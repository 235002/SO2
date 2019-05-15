#!/bin/bash

postcode="50-306 Wroclaw";
name="Jakub Pawlowski";
date1="2018-06-09";
date2="2018.06.09";
email="jakub.pawlowski@wp.pl";

regex="^([0-9]{2}-[0-9]{3}) ([a-zA-Z][-]{0,1})*$";
regex2="^([A-Z][a-z]{2,}[\n ]){1,2}[A-Z][a-z]{2,}(\-[A-Z][a-z]{2,}){0,1}$"
regex3="^([1-2][0-9]{3})\-((0[1-9])|(1[0-2]))\-((0[1-9])|([1-2][0-9])|(3[0-1]))$"
regex4="^([1-2][0-9]{3})\.((0[1-9])|(1[0-2]))\.((0[1-9])|([1-2][0-9])|(3[0-1]))$"		
regex5="^[0-9|a-z|_|-|.]+@[0-9|a-z|_|-]+\.[a-z]{2,3}$"

if [[ $postcode =~ $regex ]]; then
	echo "Postcode matched $postcode"
else
	echo "Postcode not matched"
fi

if [[ $name =~ $regex2 ]]; then
	echo "Name matched $name"
else
	echo "Name not matched"
fi

if [[ $date1 =~ $regex3 ]]; then
	echo "Date(1) matched $date1"
else
	echo "Date(1) not matched"
fi

if [[ $date2 =~ $regex4 ]]; then
	echo "Date(2) matched $date2"
else
	echo "Date(2) not matched"
fi

if [[ $email =~ $regex5 ]]; then
	echo "Email matched $email"
else
	echo "Email not matched"
fi
