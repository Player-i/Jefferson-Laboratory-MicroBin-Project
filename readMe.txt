Guide to create a MultiDimentional table using the data of Fall 2018 and Spring 2019 (EP->EPX) (Jefferson Laboratory)

Files: Location: ifarm ( /work/clas12/danieltc/MicroBin1.0/)  
Runner: MicroBin.C https://github.com/Player-i/MicroBin-Project
Text File: microBin.txt
Format of Text File: #Bin in PT  | #Bin in Q2 | #Bin in x | #Bin in zeta | #Bin in phi | Mean PT | N+ | N- | Mean x | Mean Q2 | Mean zeta | Mean phi |


The Runner consists of four nested loops, allowing us to iterate through all possible combinations of bins for our variables (pT, Q2, x, zeta, phi). By doing so, we can obtain the values of N+, N-, and the means of these variables for each combination of bins. Once MicroBin.C is executed, it generates a text file containing a four-dimensional table in the specified format. This table serves as a valuable resource for replicating our analysis and assists anyone interested in reproducing our study.
