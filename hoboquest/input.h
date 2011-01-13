#ifndef HOBO_INPUT
#define HOBO_INPUT

#include <string>
#include <stdexpect>

using std::string;

namespace hoboquest {
	// Available actions
	enum Action { UNKNOWN, GO, USE, PICKUP, DROP, DIE, QUIT, EXIT };
	string action_names[] = { "", "go", "use", "pickup", "drop", "die", "quit", "exit" };

	// Command structure
	typedef struct {
		Action action;
		string target;
	} Command;

	// Input exception
	class invalid_input: public std::logic_error {
		public:
			invalid_input() : logic_error("invalid input") {}
			invalid_input(const std::string &what) : logic_error(what) {}
	};

	class Input {
		Command parse(string in) {
			size_t space = in.find(' ');
			if (space == string::npos)
				throw invalid_input("missing target for action");

			Action action = to_action(in.substr(0, space));
			if (action == UNKNOWN)
				throw invalid_input("unknown action");

			string target = in.substr(space+1, string::npos);
			if (target.length() < 1)
				throw invalid_input("invalid target for action");

			Command command = { action, target };
			return command;
		}

		Action to_action(string in) {
			int n_actions = sizeof(action_names) / sizeof(*action_names);
			for (int i = 1; i < n_actions; ++i)
				if (in == action_names) return (Action) i;
			return UNKNOWN;
		}
	};
}

#endif
