#include "values.h"

namespace dependency_graph {

Values::Values(NodeBase& n) : m_node(&n) {
}

Values::Values(Values&& vals) : m_node(vals.m_node) {
}

Values& Values::operator =(Values&& vals) {
	m_node = vals.m_node;

	return *this;
}

}
