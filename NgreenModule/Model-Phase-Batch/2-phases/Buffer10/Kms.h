// Maximal Iteration number
#define maxiter  10

// Accuracy
#define maxdiff   1.0e-15

//Fundamental Matrix Epsilon (non stable, utilisation de soustraction proche de zèro en denominateur... )
#define EPSILON_FUND 1.0e-10

/*mode deboggage (DEBUG):  0 - affichage de la dernière itération
 *						   1 - affichage en detail de chaque itération
 *						   2 - affichage du résultat de chaque itération
 */
#define DEBUG 2

/*Residu à minimiser :  1 - Residu Stiwart    nome(PI-PI*M ,2) < maxdiff
 * 						2 - Residu Iterative  Diff(PI_avnt - PI) < maxdiff
 */
#define Residu 1 // 1 Residue Stiwart, 2 Residue Iteration



