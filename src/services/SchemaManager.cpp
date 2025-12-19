//
// Created by victoria on 12/7/25.
//

#include "./"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void SchemaManager::loadFromJson(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo JSON: " + path);
    }

    json j;
    try {
        file >> j;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error al parsear JSON: ") + e.what());
    }

    // Validar sección columns
    if (!j.contains("columns") || !j["columns"].is_array()) {
        throw std::runtime_error("JSON inválido: falta array 'columns'");
    }

    schema.columns.clear();

    for (const auto& colJson : j["columns"]) {
        if (!colJson.contains("name") || !colJson["name"].is_string()) {
            throw std::runtime_error("Columna sin nombre válido en JSON");
        }

        ColumnSchema col;
        col.name = colJson["name"].get<std::string>();

        // Procesar reglas
        if (colJson.contains("rules")) {
            if (!colJson["rules"].is_array()) {
                throw std::runtime_error("Las reglas deben ser un array");
            }

            for (const auto& ruleJson : colJson["rules"]) {
                if (!ruleJson.contains("rule") || !ruleJson["rule"].is_string()) {
                    throw std::runtime_error("Regla sin 'rule' válido");
                }

                RuleDefinition rule;
                rule.ruleName = ruleJson["rule"].get<std::string>();

                // params es opcional
                if (ruleJson.contains("params")) {
                    if (!ruleJson["params"].is_array()) {
                        throw std::runtime_error("'params' debe ser un array");
                    }
                    for (const auto& param : ruleJson["params"]) {
                        rule.params.push_back(param.get<std::string>());
                    }
                }

                col.rules.push_back(rule);
            }
        }

        schema.columns.push_back(std::move(col));
    }
}
