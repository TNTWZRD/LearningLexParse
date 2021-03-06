// Code Written and maintained by Daniel Jajliardo @ TheTechSphere
// Copywrite 2017 Daniel Jajliardo @ TheTechSphere
// This is a small utiliy file.
// Version 0.05 Updated 01/21/17 Daniel Jajliardo

#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

#pragma once

namespace smallutils {

	/*
	* Program to demostrate the use of template class and associative array.
	* By Arnav Mukhopadhyay LINES 20-64
	*/

	using namespace std;

	template <class T>
	class AssocArray
	{
	private:
		typedef struct _Data
		{
			T data;
			string name;
		} Data;
		vector<Data> stack;
	public:
		long Size()
		{
			return stack.size();
		}

		bool IsItem(string name)
		{
			for (int i = 0; i<Size(); i++)
			{
				if (stack[i].name == name)
					return true;
			}
			return false;
		}

		bool AddItem(string name, T data)
		{
			if (IsItem(name))
				return false;
			Data d;
			d.name = name;
			d.data = data;
			stack.push_back(d);
			return true;
		}

		T& operator [] (string name)
		{
			for (int i = 0; i<Size(); i++)
			{
				if (stack[i].name == name)
					return stack[i].data;
			}
			long idx = Size();
			Data d;
			d.name = name;
			stack.push_back(d);
			return stack[idx].data;
		}

		string GetItemName(long index)
		{
			if (index<0)
				index = 0;
			for (int i = 0; i<Size(); i++)
				if (i == index)
					return stack[i].name;
			return "";
		}

		T& operator [] (long index)
		{
			if (index < 0)
				index = 0;
			for (int i = 0; i<Size(); i++)
			{
				if (i == index)
					return stack[i].data;
			}
			return stack[0].data;
		}
	};

	static std::string intToString(int i) {
		char intStr[50];
		_itoa(i, intStr, 10);
		return std::string(intStr);
	}

	static std::string replaceInString(std::string in, char del, char rep) {
		std::replace(in.begin(), in.end(), del, rep);
		return in;
	}

	// New ISO Standard Date/Time Formats
	static std::string getISODate() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		std::string Year, Mon, mDay;

		Year = intToString(now->tm_year + 1900);

		if (now->tm_mon + 1 <= 9)
			Mon = "0" + intToString(now->tm_mon + 1);
		else
			Mon = intToString(now->tm_mon + 1);

		if (now->tm_mday <= 9)
			mDay = "0" + intToString(now->tm_mday);
		else
			mDay = intToString(now->tm_mday);

		return std::string(Year + '-' + Mon + "-" + mDay);
	}

	static std::string getISOTime() {
		time_t t = time(0);
		struct tm * now = localtime(&t);
		std::string Hour, Min, Sec;

		if (now->tm_hour + 1 <= 9)
			Hour = "0" + intToString(now->tm_hour + 1);
		else
			Hour = intToString(now->tm_hour + 1);

		if (now->tm_min <= 9)
			Min = "0" + intToString(now->tm_min);
		else
			Min = intToString(now->tm_min);

		if (now->tm_sec <= 9)
			Sec = "0" + intToString(now->tm_sec);
		else
			Sec = intToString(now->tm_sec);

		return std::string(Hour + ':' + Min + ":" + Sec + "Z");
	}

	static std::string getISOTimeStamp() {
		return getISODate() + "T" + getISOTime();
	}

};