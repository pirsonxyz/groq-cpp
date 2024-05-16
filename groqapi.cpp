#include "nlohmann/json.hpp"
#include <format>
#include <cpr/cpr.h>
#include "groqapi.h"
using json = nlohmann::json;

std::string createChatCompletion(const std::string& prompt, const std::string& model, std::string api_key) {
    const std::vector<std::string> valid_models = {"llama3-8b-8192", "llama3-70b-8192", "mixtral-8x7b-32768", "gemma-7b-it"};
    bool is_valid = (std::find(valid_models.begin(), valid_models.end(), model) != valid_models.end());
    if (is_valid) {
        std::string payload = R"({"messages": [{"role": "user", "content": "Explain the importance of fast language models"}], "model": "llama3-8b-8192"})";
        json data = json::parse(payload);
        data["messages"][0]["content"] = prompt;
        data["model"] = model;
        data = data.dump();
        cpr::Response r = cpr::Post(cpr::Url{"https://api.groq.com/openai/v1/chat/completions"},
                                    cpr::Header{{"Content-Type", "application/json"}},
                                    cpr::Header{{"Authorization", std::format("Bearer {}",api_key)}}, cpr::Body(data));
        json response = json::parse(r.text);
        std::string text = response["choices"][0]["message"]["content"];
        return text;
    } else {
        return "Invalid Model!";
    }
}
