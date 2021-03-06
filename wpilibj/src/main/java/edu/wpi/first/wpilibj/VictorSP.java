/*----------------------------------------------------------------------------*/
/* Copyright (c) 2008-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.wpi.first.wpilibj;

import edu.wpi.first.hal.FRCNetComm.tResourceType;
import edu.wpi.first.hal.HAL;
import edu.wpi.first.wpilibj.smartdashboard.SendableRegistry;

/**
 * VEX Robotics Victor SP Speed Controller.
 *
 * <p>Note that the VictorSP uses the following bounds for PWM values. These values should work
 * reasonably well for most controllers, but if users experience issues such as asymmetric
 * behavior around the deadband or inability to saturate the controller in either direction,
 * calibration is recommended. The calibration procedure can be found in the VictorSP User Manual
 * available from CTRE.
 *
 * <p><ul>
 * <li>2.004ms = full "forward"
 * <li>1.520ms = the "high end" of the deadband range
 * <li>1.500ms = center of the deadband range (off)
 * <li>1.480ms = the "low end" of the deadband range
 * <li>0.997ms = full "reverse"
 * </ul>
 */
public class VictorSP extends PWMSpeedController {
  /**
   * Constructor.
   *
   * @param channel The PWM channel that the VictorSP is attached to. 0-9 are
   *        on-board, 10-19 are on the MXP port
   */
  public VictorSP(final int channel) {
    super(channel);

    setBounds(2.004, 1.52, 1.50, 1.48, 0.997);
    setPeriodMultiplier(PeriodMultiplier.k1X);
    setSpeed(0.0);
    setZeroLatch();

    HAL.report(tResourceType.kResourceType_VictorSP, getChannel() + 1);
    SendableRegistry.setName(this, "VictorSP", getChannel());
  }
}
