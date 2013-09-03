// 该程序参加湖南大学第四届机器人编程大赛获得冠军
//@author: guanchao
package guanChao;

import java.awt.Color;
import java.awt.geom.Point2D;
import java.io.PrintStream;
import robocode.*;

public class Robocode extends AdvancedRobot
{

    public Robocode()
    {
        enemy = new enemyMessage();
        noTarget = true;
        count = 0;
    }

    public void run()
    {
        doInit();
        do
        {
            while(noTarget) 
            {
                setTurnRadarRightRadians((1.0D / 0.0D));
                execute();
            }
            doScan();
            doMove();
            System.out.println(count);
            doFire();
            noTarget = true;
            execute();
        } while(true);
    }

    public void onScannedRobot(ScannedRobotEvent e)
    {
        if(target == null)
            target = e.getName();
        if(!e.getName().equals(target))
            if(e.getDistance() < enemy.distance && e.getEnergy() < enemy.energy)
                target = e.getName();
            else
                return;
        noTarget = false;
        enemy.updateStat(e, this);
    }

    public void onHitRobot(HitRobotEvent e)
    {
        target = e.getName();
    }

    public void onHitByBullet(HitByBulletEvent e)
    {
        if(target == null)
            target = e.getName();
        else
        if(enemy.distance > 400D && enemy.energy > 20D)
            target = e.getName();
        else
            return;
    }

    public void doInit()
    {
        target = null;
        setScanColor(Color.blue);
        setAdjustGunForRobotTurn(true);
        setAdjustRadarForGunTurn(true);
    }

    public void onRobotDeath(RobotDeathEvent e)
    {
        if(e.getName() != target)
        {
            return;
        } else
        {
            target = null;
            return;
        }
    }

    public void doScan()
    {
        double RadarOffset = Functions.normalizeBearing(enemy.direction - getRadarHeadingRadians());
        setTurnRadarRightRadians(RadarOffset * 1.2D);
    }

    public void doMove()
    {
        double myX = getX();
        double myY = getY();
        if(Math.abs(getDistanceRemaining()) < 1.0D)
        {
            count++;
            double nextX;
            double nextY;
            if(count == 1)
            {
                nextX = 50D;
                nextY = 50D;
            } else
            {
                nextX = Math.random() * 200D + 50D;
                nextY = Math.random() * 200D + 50D;
            }
            double turnAngle = Functions.getAngle(myX, myY, nextX, nextY);
            turnAngle = Functions.normalizeBearing(turnAngle - getHeadingRadians());
            double moveDistance = Point2D.distance(myX, myY, nextX, nextY);
            double moveDirection = 1.0D;
            if(Math.abs(turnAngle) > 1.5707963267948966D)
            {
                turnAngle = Functions.normalizeBearing(turnAngle + 3.1415926535897931D);
                moveDirection = -1D;
            }
            setTurnRightRadians(turnAngle);
            setAhead(moveDirection * moveDistance);
        }
    }

    public void doFire()
    {
        double bulletPower = Functions.calcFirePower(enemy.energy, enemy.distance);
        double bulletVelocity = 20D - 3D * bulletPower;
        double headingOffset = (enemy.headingRadian - enemy.prevHeadingRadian) + 1.0000000000000001E-005D;
        System.out.println((new StringBuilder("enemy.headingRadian")).append(enemy.headingRadian).toString());
        System.out.println((new StringBuilder("enemy.prevHeadingRadian")).append(enemy.prevHeadingRadian).toString());
        System.out.println(headingOffset);
        double r = enemy.velocity / headingOffset;
        double predictDirection = 0.0D;
        double enemyDistance = enemy.distance;
        for(int i = 0; i < 4; i++)
        {
            double bulletTravelTime = enemyDistance / bulletVelocity;
            double predictHeadingRadian = enemy.headingRadian + headingOffset * bulletTravelTime;
            double predictX = (enemy.xCoordinate - r * Math.cos(predictHeadingRadian)) + r * Math.cos(enemy.headingRadian);
            double predictY = (enemy.yCoordinate + r * Math.sin(predictHeadingRadian)) - r * Math.sin(enemy.headingRadian);
            predictDirection = Functions.getAngle(getX(), getY(), predictX, predictY);
            enemyDistance = Point2D.distance(getX(), getY(), predictX, predictY);
        }

        double gunOffset = Functions.normalizeBearing(predictDirection - getGunHeadingRadians());
        setTurnGunRightRadians(gunOffset);
        if(getGunHeat() == 0.0D)
            setFire(bulletPower);
    }

    enemyMessage enemy;
    String target;
    boolean noTarget;
    int count;
}
