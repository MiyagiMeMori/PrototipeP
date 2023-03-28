#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>

class UUID {

protected:
	unsigned char UuidData[16];
};

class Device {
public:

protected:
	std::string Name_;
	unsigned char UuidData_[16]; //UUID UuidData_;
};

class BioData {
public:
	char D[9]; //not int
};

class BiometricScanner : virtual Device {
public:

	BiometricScanner(char BioStandart[9], char BioData[9])
		//: BioStandart_(BioStandart), BioData_(BioData)
	{
		for (size_t i = 0; i != 9; ++i) {
			BioStandart_[i] = rand();
			BioData_[i] = rand();
		}
	}
	
	bool BioTest() {
		if (BioStandart_ == BioData_) { return true; }
		else { return false; }
	}

private:
	//BioData BioStandart_, BioData_;
	char BioStandart_[9];
	char BioData_[9];
};

class Sensor : virtual Device {
public:
	bool Anxiety() { return (rand() % 1); } //тревога 
};

class Server {
public:

	void AddScanner(BiometricScanner Scnnr) {
		bScanners.push_back(Scnnr);
	}
	void AddSensor(Sensor Snsr) {
		Sensors.push_back(Snsr);
	}

	//template <typename T>
	void Info() {
		auto ItScnnrs = bScanners.begin();
		while (ItScnnrs != bScanners.end()) { 
			
			ItScnnrs++;
		}
		auto ItSnsrs = Sensors.begin();
		while (ItSnsrs != Sensors.end()) {
			ItSnsrs++;
		}
	}

	void PutScanner(BiometricScanner Scan) { //
		bScanners.push_back(Scan);
	}
	void PutSensor(Sensor Sens) {
		Sensors.push_back(Sens);
	}

protected:
	std::vector<BiometricScanner> bScanners;
	std::vector<Sensor> Sensors;
};

