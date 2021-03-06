#pragma once

#include <boost/noncopyable.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/signals2.hpp>

#include <dependency_graph/graph.h>

#include "config.h"
#include "undo_stack.h"
#include "index.h"

class QMainWindow;

namespace possumwood {

/// App is a singleton, instantiated explicitly in main.cpp.
/// Holds global data about the application.
class App : public boost::noncopyable {
	public:
		static App& instance();

		App();
		~App();

		dependency_graph::Graph& graph();

		const boost::filesystem::path& filename() const;

		void newFile();
		void loadFile(const boost::filesystem::path& fn);
		void saveFile();
		void saveFile(const boost::filesystem::path& fn);

		QMainWindow* mainWindow() const;
		void setMainWindow(QMainWindow* win);

		void setTime(float time);
		float time() const;
		boost::signals2::connection onTimeChanged(std::function<void(float)> fn);

		Config& sceneConfig();

		UndoStack& undoStack();

		Index& index();

	protected:
	private:
		static App* s_instance;

		dependency_graph::Graph m_graph;
		boost::filesystem::path m_filename;

		QMainWindow* m_mainWindow;

		float m_time;
		boost::signals2::signal<void(float)> m_timeChanged;

		Config m_sceneConfig;

		UndoStack m_undoStack;

		/// Allows mapping back and forward between UI classes, and underlying data model.
		/// Also stores the Drawable class instances (to be replaced with a scene graph, eventually).
		Index m_index;
};

}
