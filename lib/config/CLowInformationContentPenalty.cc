/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */

#include <config/CLowInformationContentPenalty.h>

#include <config/CAutoconfigurerParams.h>
#include <config/CDataSummaryStatistics.h>
#include <config/CDetectorSpecification.h>
#include <config/CFieldStatistics.h>
#include <config/CTools.h>

#include <cmath>

namespace ml
{
namespace config
{
namespace
{
const double LOG_MIN = 0.5 * std::log(0.9 * constants::DETECTOR_SCORE_EPSILON / constants::MAXIMUM_DETECTOR_SCORE);
}

CLowInformationContentPenalty::CLowInformationContentPenalty(const CAutoconfigurerParams &params) :
        CPenalty(params)
{}

CLowInformationContentPenalty *CLowInformationContentPenalty::clone() const
{
    return new CLowInformationContentPenalty(*this);
}

std::string CLowInformationContentPenalty::name() const
{
    return "low information content";
}

void CLowInformationContentPenalty::penaltyFromMe(CDetectorSpecification &spec) const
{
    if (config_t::isInfoContent(spec.function()))
    {
        if (const CFieldStatistics *stats = spec.argumentFieldStatistics())
        {
            if (const CCategoricalDataSummaryStatistics *summary = stats->categoricalSummary())
            {
                // Note that the empirical entropy is maximized when
                double minimumLength = static_cast<double>(summary->minimumLength());
                double maximumLength = static_cast<double>(summary->maximumLength());
                double cardinality   = static_cast<double>(summary->distinctCount());
                double entropy       = summary->entropy();
                double penalty = cardinality == 1.0 ?
                                 0.0 :   std::exp(CTools::interpolate(this->params().lowLengthRangeForInfoContent(),
                                                                      this->params().minimumLengthRangeForInfoContent(),
                                                                      0.0, LOG_MIN, maximumLength - minimumLength))
                                       * std::exp(CTools::interpolate(this->params().lowMaximumLengthForInfoContent(),
                                                                      this->params().minimumMaximumLengthForInfoContent(),
                                                                      0.0, LOG_MIN, maximumLength))
                                       * std::exp(CTools::logInterpolate(this->params().lowEntropyForInfoContent(),
                                                                         this->params().minimumEntropyForInfoContent(),
                                                                         0.0, LOG_MIN, entropy / std::log(cardinality)))
                                       * std::exp(CTools::logInterpolate(this->params().lowDistinctCountForInfoContent(),
                                                                         this->params().minimumDistinctCountForInfoContent(),
                                                                         LOG_MIN, 0.0, cardinality));
                std::string description;
                if (penalty < 1.0)
                {
                    description = "There is weak evidence that '"
                                 + *spec.argumentField() + "' carries information";
                }
                spec.applyPenalty(penalty, description);
            }
        }
    }
}

}
}
