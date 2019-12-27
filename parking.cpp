/*
	File name: parking.cpp
	Author: Dharod Archit
	Date: 27.12.2019
	Version: 1.0.0

	Function Definitions for:
	1. calculate_fee
	2. calculate_parking_time
	3. Minutes_to_vector
	4. convert_to_coins
	5. Bill_customer
*/

#include "parking.h"

// 1.calculate_fee

double calculate_fee(double parking_hours)
{
	double fee = 0; //initializing fee. Variable to hold the fee.
	if (parking_hours <= 0.5) //case 1: upto half an hour
	{
		return fee; //fee for upto half an hour is 0
	}
	else if (parking_hours >0.5 && parking_hours <=4) //case 2: from 0.5 hours until 4 hours
	{
		int factor;
		factor = parking_hours / 0.50001; //implicit conversion to type int to discard values after decimal
		return fee = factor * 1; //0.5 hour factor * 1 Eur - returned as a double.
	}
	else if (parking_hours > 4)
	{
		const int fee_upto_4_hours = 7; // 1 Eur per 0.5 hours - upto 4th hour
		const double hourly_fee = 1.5; 
		int additional_hour = 1 + (int)((parking_hours-4) / 1.0001);
		//the factor "additional_hour" counts the entire hour, even if parking time is less than an hour.

		fee = fee_upto_4_hours + (additional_hour * hourly_fee);
        return fee;
	}

}

// 2.calculate_parking_time
std::vector <int> calculate_parking_time(double amount)
{
/*
this calculates the parking time in minutes first, which is then converted to 
the vector using another function Minutes_to_vector
*/
	std::vector<int> parking_time = { 30,0,0,0 }; //vector for output
	int Total_parking_time = 0;
	const int free_parking_time = 30; //minutes
	const int first_four_hours = 240; //minutes
	const double cost_first_four_hours = 7;//Eur

	if (amount < 1) //default case: allows 30 min parking
	{
		return parking_time;
    }
	else  //calculates parking time for amount >=1 Eur
	{
		if (amount < 8) //upto 4 hours parking costs 1 Eur/30 min; 7,99 Eur also gives 4 hours parking.
		{
			Total_parking_time = free_parking_time + ((int)amount * 30);
		}
		else //different case for 8 eur onwards = 4 hour onwards 
		{
			double excess_money = amount - cost_first_four_hours; //leftover money after the 1 eur tarif for 4 hours.
			double factor = excess_money / 1.5; //factor used to calculate the parking time
			int extra_parking_time = (int)factor * 60;
			Total_parking_time = extra_parking_time + first_four_hours;
		}
	}
	parking_time = Minutes_to_vector(Total_parking_time);
	return parking_time;
}



// 3. Minutes_to_vector

std::vector<int> Minutes_to_vector(int minutes)
{
	std::vector<int> dummy_vector = { 0,0,0,0 };
	dummy_vector.at(3) = minutes / (365 * 24 * 60); //Years
	minutes %= (365 * 24 * 60);

	dummy_vector.at(2) = minutes / (24 * 60); //Days
	minutes %= (24 * 60);

	dummy_vector.at(1) = minutes / (60); //Hours
	minutes %= (60);

	dummy_vector.at(0) = minutes; //Minutes

	return dummy_vector;
}



// 5. convert_to_coins
std::vector <int> convert_to_coins(double return_amount)
{
	std::vector<int> dummy_vector(8);
	int amount_in_cents = round(return_amount * 100);


	dummy_vector.at(0) = amount_in_cents / (2 * 100); //2 Eur
	amount_in_cents %= (2 * 100);

	dummy_vector.at(1) = amount_in_cents / (1 * 100); //1 Eur
	amount_in_cents %= (1 * 100);

	dummy_vector.at(2) = amount_in_cents / (5 * 10); //0.50 Eur
	amount_in_cents %= (5 * 10);

	dummy_vector.at(3) = amount_in_cents / (2 * 10); //0.20 Eur
	amount_in_cents %= (2 * 10);

	dummy_vector.at(4) = amount_in_cents / (1 * 10);//0.10 Eur
	amount_in_cents %= (1 * 10);

	dummy_vector.at(5) = amount_in_cents / (5 * 1);//0.05 Eur
	amount_in_cents %= (5 * 1);

	dummy_vector.at(6) = amount_in_cents / (2 * 1);// 0.02 Eur
	amount_in_cents %= (2 * 1);

	dummy_vector.at(7) = amount_in_cents / (1 * 1);// 0.01 Eur
	amount_in_cents %= (1 * 1);

	return dummy_vector;
}


// 5. bill_customer
std::vector <int> bill_customer(double parking_hours, double amount)
{
	std::vector<int> change_vector(8); //this is the change to be returned/needed.

	// 1. The cost for given parking_hours is calculated:
	double cost_of_parking = calculate_fee(parking_hours);

	// 2. cost_of_parking is compared to amount 
	double amount_difference = amount - cost_of_parking;

	// 3. the difference is converted to a vector and returned
	change_vector = convert_to_coins(amount_difference);
	return change_vector;
}