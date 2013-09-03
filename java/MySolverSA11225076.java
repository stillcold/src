package myProject;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.Random;

/**
 * Use all cars to do the job, and try to get a better solution by hillClimber.
 * For each customer, chose the car whose path is the shortest.
 * If the capacity of picked car can't fulfill the demand, 
 *    then chose the biggest one instead.
 * @author GC.
 * 该程序在2011-2012科大软院的实用算法设计课上获得冠军。
 * Copyright (c) 2011-2013 Chao Guan
 */
public class MySolverSA11225076 {

	public static final void main(final String[] args) throws Throwable {
		BufferedReader br;
		String source, oldS, dest;
		Problem p;
		Solution s;
		p = new Problem();
		br = new BufferedReader(new InputStreamReader(System.in));
		oldS = null;
		for (;;) {
			do {
				source = br.readLine();
				if (source == null) {
					return;
				}
				source = source.trim();
			} while (source.length() <= 0);
			do {
				dest = br.readLine();
				if (dest == null) {
					return;
				}
				dest = dest.trim();
			} while (dest.length() <= 0);

			if ((oldS == null) || (!(source.equals(oldS)))) {
				p.readFile(new File(source));
			}
			oldS = source;
			s = solve(p);
			if (s != null) {
				s.writeFile(new File(dest));
			}
			System.out.println("OK"); //$NON-NLS-1$
			System.out.flush();
		}
	}

	public static final long TIME_PER_RUN = (Evaluator.MAX_TIME / (11 * (3 + Evaluator.MIN_RUNS)));

	/**
	 * solve the problem
	 * 
	 * @param p
	 *            the problem
	 * @return the solution
	 */
	public static final Solution solve(final Problem p) {
		/* *
		 * this function is designed for a particular input file.
		 */
		long t = (System.currentTimeMillis() + TIME_PER_RUN);
		Solution a, b;
		int numOfCustomer = p.customerCount();
		int numOfDepot = p.depotCount();
		int numOfCar = p.carCount();
		int pickedCar = 0;
		int biggestCar, biggestCapacity, lengthOFNormal;
		int nextDepot, nextCustomer;
		int nextNode, tempNode;
		// for the shortest path.

		double distance, shortestDis;
		double disBetweenDep, shortestDisBetweenD;
		// the genotype! it is the basic of this algorithm.
		int[] sequence = new int[numOfCustomer];
		int[] mutatedSequence = new int[numOfCustomer];
		int mutateNum;
		// if the solution is invalid, it must have something to do with this
		// array.
		int[] capacity = new int[numOfCar];
		boolean[] flagOfEachCar = new boolean[numOfCar];
		int[] lengthOfEachCar = new int[numOfCar];
		lengthOFNormal = (int) (4 * numOfCustomer / numOfCar);
		int shortestPath = lengthOFNormal;
		int[][] path = new int[numOfCar][lengthOFNormal];
		int[] pathForBiggest = new int[3 * numOfCustomer];
		double x, y;
		int[][] dummy;
		int[] temp;
		Random r = new Random();

		// find the biggest car, we will use that one
		biggestCar = 0;
		biggestCapacity = p.getCarCapacity(0);
		for (int i = p.carCount(); (--i) > 0;) {
			int c = p.getCarCapacity(i);
			if (c > biggestCapacity) {
				biggestCar = i;
				biggestCapacity = c;
			}
		}
		// Initiate the sequence.
		for (int i = 0; i < numOfCustomer; i++) {
			sequence[i] = i + numOfDepot;
		}
		sequence[0] = numOfDepot;
		for (int i = 0; i < numOfCustomer-1; i++){
			shortestDisBetweenD = p.getDistance(i, i+1);
			nextNode = i+1;
			for (int j = i+1; j < numOfCustomer; j++){
				disBetweenDep = p.getDistance(i, j);
				if (shortestDisBetweenD > disBetweenDep){
					nextNode = j;
				}
			}
			tempNode = sequence[i+1];
			sequence[i+1] = sequence[nextNode];
			sequence[nextNode] = tempNode;
		}
//		for (int i = 0; i < numOfCustomer; i++){
//			System.out.print(sequence[i]+" ");
//		}
//		System.out.println();
		
		// Initiate some data structure.
		for (int i = 0; i < numOfCar; i++) {
			capacity[i] = p.getCarCapacity(i);
			path[i][0] = p.getCarDepot(i);
			lengthOfEachCar[i] = 1;
		}
		pathForBiggest[0] = p.getCarDepot(biggestCar);
		biggestCapacity = p.getCarCapacity(biggestCar);

		// Get a solution.
		for (int i = 0; i < numOfCustomer; i++) {
			// get next customer.
			nextCustomer = sequence[i];

			// get next car.
			if (numOfCar == 1) {
				pickedCar = biggestCar;
			} else {
				// initiate the flag first.
				for (int j = 0; j < numOfCar; j++) {
					flagOfEachCar[j] = true;
				}

				// then kick the invalid car.
				for (int j = 0; j < numOfCar; j++) {
					if (p.getCarCapacity(j) < p.getNodeDemand(nextCustomer)) {
						flagOfEachCar[j] = false;
					}
				}

				// get one available car as a start.
				for (int j = 0; j < numOfCar; j++) {
					if (flagOfEachCar[j] == true) {
						shortestPath = lengthOfEachCar[j];
						pickedCar = j;
						break;
					}
				}

				// get the car whose path is the shortest.
				for (int j = 0; j < numOfCar; j++) {
					if (flagOfEachCar[j] == false) {
						continue;
					} else {
						if (shortestPath > lengthOfEachCar[j]) {
							shortestPath = lengthOfEachCar[j];
							pickedCar = j;
						}
					}
				}

				// kick the car whose path is full.
				if (lengthOfEachCar[pickedCar] >= lengthOFNormal - 1) {
					pickedCar = biggestCar;
				}
			}// get next car.
				// System.out.println(pickedCar);

			// The biggest car use a different data structure.
			if (pickedCar != biggestCar) {
				if (p.getNodeDemand(nextCustomer) > capacity[pickedCar]) {
					nextDepot = 0;
					shortestDis = p.getDistance(
							path[pickedCar][lengthOfEachCar[pickedCar] - 1],
							nextDepot)
							+ p.getDistance(nextDepot, nextCustomer);
					for (int j = 1; j < numOfDepot; j++) {
						distance = p
								.getDistance(
										path[pickedCar][lengthOfEachCar[pickedCar] - 1],
										j)
								+ p.getDistance(j, nextCustomer);
						if (shortestDis > distance) {
							shortestDis = distance;
							nextDepot = j;
						}
					}
					path[pickedCar][lengthOfEachCar[pickedCar]++] = nextDepot;
					capacity[pickedCar] = p.getCarCapacity(pickedCar);
				}
				path[pickedCar][lengthOfEachCar[pickedCar]++] = nextCustomer;
				capacity[pickedCar] -= p.getNodeDemand(nextCustomer);
			} else {
				if (p.getNodeDemand(nextCustomer) > biggestCapacity) {
					nextDepot = 0;
					shortestDis = p.getDistance(
							pathForBiggest[lengthOfEachCar[biggestCar] - 1],
							nextDepot)
							+ p.getDistance(nextDepot, nextCustomer);
					for (int j = 1; j < numOfDepot; j++) {
						distance = p
								.getDistance(
										pathForBiggest[lengthOfEachCar[biggestCar] - 1],
										j)
								+ p.getDistance(j, nextCustomer);
						if (shortestDis > distance) {
							shortestDis = distance;
							nextDepot = j;
						}
					}
					pathForBiggest[lengthOfEachCar[biggestCar]++] = nextDepot;
					biggestCapacity = p.getCarCapacity(biggestCar);
				}
				pathForBiggest[lengthOfEachCar[biggestCar]++] = nextCustomer;
				biggestCapacity -= p.getNodeDemand(nextCustomer);
			}

		}// get a solution.
			// outputPath(path, numOfCar, lengthOFNormal);
			// outputSequence(pathForBiggest, lengthOfEachCar[biggestCar]);
			// for (int i = 0; i < pathForBiggest.length; i++) {
			// System.out.print(pathForBiggest[i] + " ");
			// }
			// System.out.println();
		dummy = new int[numOfCar][];
		for (int i = 0; i < numOfCar; i++) {
			if (i == biggestCar)
				continue;
			temp = new int[lengthOfEachCar[i]];
			System.arraycopy(path[i], 0, temp, 0, lengthOfEachCar[i]);
			dummy[i] = temp;
		}
		temp = new int[lengthOfEachCar[biggestCar]];
		// System.out.println(lengthOfEachCar[biggestCar]);
		System.arraycopy(pathForBiggest, 0, temp, 0,
				lengthOfEachCar[biggestCar]);
		dummy[biggestCar] = temp;
		// for (int i = 0; i < numOfCar; i++) {
		// for (int j = 0; j < dummy[i].length; j++) {
		// System.out.print(dummy[i][j] + " ");
		// }
		// System.out.println();
		// }
		a = new Solution();
		a.setData(dummy);
		// System.out.println(p.evaluate(a));
		x = p.evaluate(a);
		// System.out.println(x);

		// optimize.
		while (System.currentTimeMillis() < t) {
			// Get the number of mutate.
			if (t - System.currentTimeMillis() > 3000) {
				mutateNum = r.nextInt(numOfCustomer);
			} else {
				mutateNum = r.nextInt((int) (numOfCustomer * 0.1));
			}
			// Mutate.
			mutatedSequence = sequence.clone();
			for (int i = 0; i < mutateNum; i++) {
				int chosed = r.nextInt(numOfCustomer);
				int t1 = mutatedSequence[chosed];
				mutatedSequence[chosed] = mutatedSequence[i];
				mutatedSequence[i] = t1;
			}

			for (int i = 0; i < numOfCar; i++) {
				capacity[i] = p.getCarCapacity(i);
				path[i][0] = p.getCarDepot(i);
				lengthOfEachCar[i] = 1;
			}
			pathForBiggest[0] = p.getCarDepot(biggestCar);
			biggestCapacity = p.getCarCapacity(biggestCar);
			// Get another solution.
			for (int i = 0; i < numOfCustomer; i++) {
				// get next customer.
				nextCustomer = mutatedSequence[i];

				// get next car.
				if (numOfCar == 1) {
					pickedCar = biggestCar;
				} else {
					// initiate the flag first.
					for (int j = 0; j < numOfCar; j++) {
						flagOfEachCar[j] = true;
					}

					// then kick the invalid car.
					for (int j = 0; j < numOfCar; j++) {
						if (p.getCarCapacity(j) < p.getNodeDemand(nextCustomer)) {
							flagOfEachCar[j] = false;
						}
					}

					// get one available car.
					for (int j = 0; j < numOfCar; j++) {
						if (flagOfEachCar[j] == true) {
							shortestPath = lengthOfEachCar[j];
							pickedCar = j;
							break;
						}
					}

					// get the car whose path is the shortest.
					for (int j = 0; j < numOfCar; j++) {
						if (flagOfEachCar[j] == false) {
							continue;
						} else {
							if (shortestPath > lengthOfEachCar[j]) {
								shortestPath = lengthOfEachCar[j];
								pickedCar = j;
							}
						}
					}

					// kick the car whose path is too full.
					if (lengthOfEachCar[pickedCar] >= lengthOFNormal - 1) {
						pickedCar = biggestCar;
					}
				}// get next car.

				if (pickedCar != biggestCar) {
					if (p.getNodeDemand(nextCustomer) > capacity[pickedCar]) {
						nextDepot = 0;
						shortestDis = p
								.getDistance(
										path[pickedCar][lengthOfEachCar[pickedCar] - 1],
										nextDepot)
								+ p.getDistance(nextDepot, nextCustomer);
						for (int j = 1; j < numOfDepot; j++) {
							distance = p
									.getDistance(
											path[pickedCar][lengthOfEachCar[pickedCar] - 1],
											j)
									+ p.getDistance(j, nextCustomer);
							if (shortestDis > distance) {
								shortestDis = distance;
								nextDepot = j;
							}
						}
						path[pickedCar][lengthOfEachCar[pickedCar]++] = nextDepot;
						capacity[pickedCar] = p.getCarCapacity(pickedCar);
					}
					path[pickedCar][lengthOfEachCar[pickedCar]++] = nextCustomer;
					capacity[pickedCar] -= p.getNodeDemand(nextCustomer);
				} else {
					if (p.getNodeDemand(nextCustomer) > biggestCapacity) {
						nextDepot = 0;
						shortestDis = p
								.getDistance(
										pathForBiggest[lengthOfEachCar[biggestCar] - 1],
										nextDepot)
								+ p.getDistance(nextDepot, nextCustomer);
						for (int j = 1; j < numOfDepot; j++) {
							distance = p
									.getDistance(
											pathForBiggest[lengthOfEachCar[biggestCar] - 1],
											j)
									+ p.getDistance(j, nextCustomer);
							if (shortestDis > distance) {
								shortestDis = distance;
								nextDepot = j;
							}
						}
						pathForBiggest[lengthOfEachCar[biggestCar]++] = nextDepot;
						biggestCapacity = p.getCarCapacity(biggestCar);
					}
					pathForBiggest[lengthOfEachCar[biggestCar]++] = nextCustomer;
					biggestCapacity -= p.getNodeDemand(nextCustomer);
				}

			}// get a solution.

			dummy = new int[numOfCar][];
			for (int i = 0; i < numOfCar; i++) {
				if (i == biggestCar)
					continue;
				temp = new int[lengthOfEachCar[i]];
				System.arraycopy(path[i], 0, temp, 0, lengthOfEachCar[i]);
				dummy[i] = temp;
			}
			temp = new int[lengthOfEachCar[biggestCar]];
			System.arraycopy(pathForBiggest, 0, temp, 0,
					lengthOfEachCar[biggestCar]);
			dummy[biggestCar] = temp;
			b = new Solution();
			b.setData(dummy);
			y = p.evaluate(b);
			if (x > y) {
				sequence = mutatedSequence.clone();
				a = b;
				x = y;
			}
			// System.out.println(x);
		}// while---optimize.
//		System.out.println(p.evaluate(a));
		return a;
	}

	public static void outputSequence(int[] sequence, int lengthOfSeq) {
		for (int i = 0; i < lengthOfSeq; i++) {
			System.out.print(sequence[i] + " ");
		}
		System.out.println();
	}

	public static void outputPath(int[][] path, int r, int c) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				System.out.print(path[i][j] + " ");
			}
			System.out.println();
		}
	}

}
