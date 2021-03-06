/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "hal/HALBase.h"
#include "hal/Types.h"

extern "C" {
void HALSIM_SetRuntimeType(HAL_RuntimeType type);
void HALSIM_WaitForProgramStart(void);
void HALSIM_SetProgramStarted(void);
HAL_Bool HALSIM_GetProgramStarted(void);
void HALSIM_RestartTiming(void);
void HALSIM_PauseTiming(void);
void HALSIM_ResumeTiming(void);
HAL_Bool HALSIM_IsTimingPaused(void);
void HALSIM_StepTiming(uint64_t delta);
void HALSIM_StepTimingAsync(uint64_t delta);

typedef int32_t (*HALSIM_SendErrorHandler)(
    HAL_Bool isError, int32_t errorCode, HAL_Bool isLVCode, const char* details,
    const char* location, const char* callStack, HAL_Bool printMsg);
void HALSIM_SetSendError(HALSIM_SendErrorHandler handler);

typedef int32_t (*HALSIM_SendConsoleLineHandler)(const char* line);
void HALSIM_SetSendConsoleLine(HALSIM_SendConsoleLineHandler handler);

}  // extern "C"
