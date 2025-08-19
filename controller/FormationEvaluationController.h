// FormationEvaluationController.h
#pragma once
#include "RadarModelDAO.h"
#include "JammerModelDAO.h"
#include "TargetModelDAO.h"
#include "RcsDataDAO.h"
#include "FormationEvaluation.h"

class FormationEvaluationController {
public:
    static double evaluateFormation(
        // int algorithmIndex,
        int condition,
        const RadarModel& transmitter,
        const RadarModel& receiver,
        const JammerModel* jammer,
        const TargetModel& target,
        const RcsData& rcs);
};