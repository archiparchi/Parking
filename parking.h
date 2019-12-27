/*
	File name: parking.h
	Author: Dharod Archit 
	Date: 27.12.2019
	Version: 1.0.0
*/
#pragma once
#include<iostream>
#include<vector>
#include<cmath>

double calculate_fee(double);
std::vector <int> calculate_parking_time(double amount);
std::vector <int> convert_to_coins(double return_amount);
std::vector <int> bill_customer(double parking_hours, double amount);
std::vector<int> Minutes_to_vector(int minutes);