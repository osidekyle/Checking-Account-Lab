/*Kyle Hawkins
CSCI 112
Ronald Burgher
Checking Account Lab*/


#include <stdio.h>
//File pointers
FILE *fpIn, *fpOut;
int feof(FILE* stream);

//Function Prototypes
void outputHeaders();
void initialBalance(double amount, double *balance, double *service, double *openBalance);
void deposit(double amount, double *balance,double *service,int *numDeposit,double *amtDeposit );
void check(double amount, double *balance, double *service, int *numCheck, double *amtCheck);
void outputSummary(int numDeposit, double amtDeposit, int numCheck, double amtCheck, double openBalance, double service, double closeBalance);

int main(void) {
	char code;
	double amount, service, balance;
	double amtCheck, amtDeposit, openBalance, closeBalance;
	int numCheck, numDeposit;

	fopen_s(&fpIn, "account.txt", "r");
	if (fpIn == NULL) {
		fprintf(fpOut,"account.txt could not be opened for input.");
		printf("account.txt could not be opened for input.");

		exit(1);
	}
	fopen_s(&fpOut, "csis.txt", "w");
	if (fpOut == NULL) {
		fprintf(fpOut,"csis.txt could not be opened for output.");
		printf("csis.txt could not be opened for output.");

		exit(1);
	}

	amount = 0.0;
	service = 0.0;
	balance = 0.0;
	amtCheck = 0.0;
	amtDeposit = 0.0;
	openBalance = 0.0;
	closeBalance = 0.0;
	numCheck = 0;
	numDeposit = 0;

	outputHeaders();


	while (!feof(fpIn)) {
		fscanf_s(fpIn, "%c %lf\n", &code, 1, &amount);
		if (code == 'I') {
			initialBalance(amount, &balance, &service, &openBalance);
		}
		else if (code == 'D') {
			deposit(amount, &balance, &service, &numDeposit, &amtDeposit);
		}
		else {
			check(amount, &balance, &service, &numCheck, &amtCheck);
		}
	}
	closeBalance = balance - service;
	outputSummary(numDeposit, amtDeposit, numCheck, amtCheck, openBalance, service, closeBalance);
	fclose(fpIn);
	fclose(fpOut);
	return 0;

}

void outputHeaders() {
	//Header
	fprintf(fpOut,"Transaction\tDeposit Check  Balance\n-----------\t------- -----  -------\n");
	printf("Transaction\tDeposit Check  Balance\n-----------\t------- -----  -------\n");

}
void initialBalance(double amount, double *balance, double *service, double *openBalance) {
	//Assigns amount value to balance, openBalance, and adds monthly 3 dollar service charge
	*openBalance = amount;
	*balance = amount;
	*service = 3;
	//Initial Balance print statement
	fprintf(fpOut,"Initial Balance\t\t\t%.2lf\n", *balance);
	printf("Initial Balance\t\t\t%.2lf\n", *balance);


}
void deposit(double amount, double *balance, double *service, int *numDeposit, double *amtDeposit) {
	//Adds 1 deposit, adds to total deposit, adds to total balance, and adds 0.03 service charge
	*numDeposit+=1;
	*amtDeposit += amount;
	*balance += amount;
	*service += 0.03;
	//Deposit print statement
	fprintf(fpOut,"Deposit\t\t%.2lf\t\t%.2lf\n", amount, *balance);
	printf("Deposit\t\t%.2lf\t\t%.2lf\n", amount, *balance);

}
void check(double amount, double *balance, double *service, int *numCheck, double *amtCheck) {
	//Adds 1 check, adds to total check, subtracts from from balance and adds 0.06 service charge
	*numCheck+=1;
	*amtCheck += amount;
	*balance=*balance - amount;
	*service += 0.06;
	//If check leaves balance under 0, 5 dollar overdraft fee
	if (*balance < 0) {
		*service += 5.00;
	}
	//Check print statement
	fprintf(fpOut,"Check\t\t\t%.2lf\t%.2lf\n", amount, *balance);
	printf("Check\t\t\t%.2lf\t%.2lf\n", amount, *balance);


}
void outputSummary(int numDeposit, double amtDeposit, int numCheck, double amtCheck, double openBalance, double service, double closeBalance){
	//Final summary print statement
	fprintf(fpOut,"\n\nSummary\n---------------------------------------------------------\nOpening Balance: %.2lf\nNumber of Deposits: %d\tAmount Deposited: %.2lf\nNumber of Checks: %d\tAmount Checked: %.2lf\nService Charges: %.2lf\nClosing Balance: %.2lf", openBalance, numDeposit, amtDeposit, numCheck, amtCheck, service, closeBalance);
	printf("\n\nSummary\n---------------------------------------------------------\nOpening Balance: %.2lf\nNumber of Deposits: %d\tAmount Deposited: %.2lf\nNumber of Checks: %d\tAmount Checked: %.2lf\nService Charges: %.2lf\nClosing Balance: %.2lf", openBalance, numDeposit, amtDeposit, numCheck, amtCheck, service, closeBalance);

}	
