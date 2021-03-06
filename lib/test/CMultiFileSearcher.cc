/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */
#include <test/CMultiFileSearcher.h>

#include <core/CDataAdder.h>
#include <core/CLogger.h>

#include <fstream>
#include <memory>
#include <utility>

namespace ml {
namespace test {

const std::string CMultiFileSearcher::JSON_FILE_EXT(".json");

CMultiFileSearcher::CMultiFileSearcher(std::string baseFilename,
                                       std::string baseDocId,
                                       std::string fileExtension)
    : m_BaseFilename(std::move(baseFilename)), m_BaseDocId(std::move(baseDocId)),
      m_FileExtension(std::move(fileExtension)) {
}

CMultiFileSearcher::TIStreamP CMultiFileSearcher::search(size_t currentDocNum, size_t limit) {
    if (limit != 1) {
        LOG_ERROR(<< "File searcher can only operate with a limit of 1");
        return TIStreamP();
    }

    // NB: The logic in here must mirror that of CMultiFileDataAdder::makeFilename()

    std::string filename(m_BaseFilename);
    if (!m_SearchTerms[0].empty()) {
        filename += '/';
        if (m_SearchTerms[0].front() == '.') {
            filename += '_';
        }
        filename += m_SearchTerms[0];
    }
    if (!m_SearchTerms[1].empty()) {
        filename += '/';
        filename += m_SearchTerms[1];
    }
    filename += '/';
    filename += core::CDataAdder::makeCurrentDocId(m_BaseDocId, currentDocNum);
    filename += m_FileExtension;

    // Failure to open the file is not necessarily an error - the calling method
    // will decide.  Therefore, return a pointer to the stream even if it's not
    // in the "good" state.
    return std::make_shared<std::ifstream>(filename.c_str());
}
}
}
