#include "json_value.h"

/**
 * @brief Semantic analysis of docker image configuration.
 * @param Root of JSON document.
 * @return true if the configuration is valid
 */
bool do_semantic_analysis (std::shared_ptr<json_value> val_);
