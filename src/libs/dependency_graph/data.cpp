#include "data.inl"

namespace dependency_graph {

std::map<std::string, std::function<std::unique_ptr<BaseData>()>>& BaseData::factories() {
	static std::map<std::string, std::function<std::unique_ptr<BaseData>()>> s_factories;
	return s_factories;
}

std::unique_ptr<BaseData> BaseData::create(const std::string& type) {
	auto it = factories().find(type);

	if(it == factories().end()) {
		std::stringstream err;
		err << "Error instantiating type '" << type << "' - no registered factory found (plugin not loaded?)";

		throw std::runtime_error(err.str());
	}

	return it->second();
}

}
