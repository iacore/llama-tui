#include "common.h"
#include "llama.h"

// example utils
namespace ex {
gpt_params parse_params(int argc, char** argv);
llama_context* load_model(gpt_params params);
}  // namespace ex
