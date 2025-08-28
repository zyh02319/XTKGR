// FormationEvaluationController.h
#pragma once
#include "RadarModelDAO.h"
#include "JammerModelDAO.h"
#include "TargetModelDAO.h"
#include "RcsDataDAO.h"
#include "FormationEvaluation.h"
#include <vector>

class FormationEvaluationController {
public:
	static double evaluateFormation(
		// int algorithmIndex,
		int condition,
		const std::vector<RadarModel>& radars,
		const JammerModel* jammer,
		const TargetModel& target,
		const RcsData& rcs);
};