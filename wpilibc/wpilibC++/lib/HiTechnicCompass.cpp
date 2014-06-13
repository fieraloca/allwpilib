/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "HiTechnicCompass.h"
#include "DigitalModule.h"
#include "I2C.h"
//#include "NetworkCommunication/UsageReporting.h"
#include "WPIErrors.h"
#include "LiveWindow/LiveWindow.h"

const uint8_t HiTechnicCompass::kAddress;
const uint8_t HiTechnicCompass::kManufacturerBaseRegister;
const uint8_t HiTechnicCompass::kManufacturerSize;
const uint8_t HiTechnicCompass::kSensorTypeBaseRegister;
const uint8_t HiTechnicCompass::kSensorTypeSize;
const uint8_t HiTechnicCompass::kHeadingRegister;

/**
 * Constructor.
 */
HiTechnicCompass::HiTechnicCompass()
	: m_i2c (NULL)
{
	m_table = NULL;
	DigitalModule *module = DigitalModule::GetInstance(1);
	if (module)
	{
		m_i2c = module->GetI2C(kAddress);

		// Verify Sensor
		const uint8_t kExpectedManufacturer[] = "HiTechnc";
		const uint8_t kExpectedSensorType[] = "Compass ";
		if ( ! m_i2c->VerifySensor(kManufacturerBaseRegister, kManufacturerSize, kExpectedManufacturer) )
		{
			wpi_setWPIError(CompassManufacturerError);
			return;
		}
		if ( ! m_i2c->VerifySensor(kSensorTypeBaseRegister, kSensorTypeSize, kExpectedSensorType) )
		{
			wpi_setWPIError(CompassTypeError);
		}

		HALReport(HALUsageReporting::kResourceType_HiTechnicCompass, 0);
		LiveWindow::GetInstance()->AddSensor("HiTechnicCompass", 1, this);
	}
}

/**
 * Destructor.
 */
HiTechnicCompass::~HiTechnicCompass()
{
	delete m_i2c;
	m_i2c = NULL;
}

/**
 * Get the compass angle in degrees.
 *
 * The resolution of this reading is 1 degree.
 *
 * @return Angle of the compass in degrees.
 */
float HiTechnicCompass::GetAngle()
{
	uint16_t heading = 0;
	if (m_i2c)
	{
		m_i2c->Read(kHeadingRegister, sizeof(heading), (uint8_t *)&heading);

		// Sensor is little endian... swap bytes
		heading = (heading >> 8) | (heading << 8);
	}
	return (float)heading;
}

void HiTechnicCompass::UpdateTable() {
	if (m_table != NULL) {
		m_table->PutNumber("Value", GetAngle());
	}
}

void HiTechnicCompass::StartLiveWindowMode() {

}

void HiTechnicCompass::StopLiveWindowMode() {

}

std::string HiTechnicCompass::GetSmartDashboardType() {
	return "HiTechnicCompass";
}

void HiTechnicCompass::InitTable(ITable *subTable) {
	m_table = subTable;
	UpdateTable();
}

ITable * HiTechnicCompass::GetTable() {
	return m_table;
}
