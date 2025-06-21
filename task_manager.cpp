#include <csignal>
#include <iostream>
#include <string>
#include <vector>

struct Task {
  std::string m_desc;
  bool status = false;
};

std::vector<Task> tasks;

void clr_buff() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Program logic
void tasks_add(std::string desc) {
  Task task;
  task.m_desc = desc;
  tasks.push_back(task);
};

void tasks_pop(int index) {
  --index;
  tasks.erase(tasks.begin() + index);
};
void tasks_print() {
  std::cout << "\nTasks: \n";
  for (size_t i{}; i < tasks.size(); ++i) {
    std::cout << i + 1 << ". " << tasks[i].m_desc << " - "
              << ((tasks[i].status) ? "Completed\n" : "Not finished yet\n");
  }
}

void tasks_conclude_task(size_t index) {
  --index;
  tasks[index].status = true;
};

void tasks_edit(size_t index, std::string desc) {
  --index;
  tasks[index].m_desc = desc;
  tasks[index].status = false;
}

void print_menu() {
  std::cout << "\n======= Tasks =======\n"
            << "1. Add a task          \n"
            << "2. Remove a task       \n"
            << "3. List                \n"
            << "4. Edit                \n"
            << "5. Conclude            \n"
            << "Press anything to exit..\n"
            << "=====================  \n"
            << "Choose:           ";
}

// Handlers
void handle_task_add() {
  std::string desc;
  std::cout << "\nEnter your task description: ";
  clr_buff();
  std::getline(std::cin, desc);
  tasks_add(desc);
  std::cout << "Task was added!\n";
}

void handle_task_pop() {
  size_t index;
  tasks_print();
  std::cout << "\nEnter task index to be removed: ";
  if (!(std::cin >> index)) {
    std::cout << "Enter a valid value!\n";
    std::cin.clear();
  }
  if (index > tasks.size() || index <= 0) {
    std::cout << "Enter a valid index!\n";
  } else {
    tasks_pop(index);
    std::cout << "Task was deleted!\n";
  }
}

void handle_task_conclude() {
  size_t index;
  tasks_print();
  std::cout << "\nEnter task index to be finished: ";
  if (!(std::cin >> index)) {
    std::cout << "Enter a valid value!\n";
    std::cin.clear();
  } else if (index > tasks.size() || index <= 0) {
    std::cout << "Enter a valid index!\n";
  } else {
    tasks_conclude_task(index);
    std::cout << "Your task was finished!\n";
  }
}

void handle_task_edit() {
  size_t index;
  std::string desc;
  std::cout << "Enter task index to be edited: ";
  if (!(std::cin >> index)) {
    std::cout << "Please enter a valid value!\n";
    std::cin.clear();
    clr_buff();
  }
  if (index > tasks.size() || index <= 0) {
    std::cout << "Please enter a valid index!\n";
    std::cin.clear();
    clr_buff();
  } else {
    std::cout << "Enter a new description for your task: ";
    clr_buff();
    if (!(std::getline(std::cin, desc))) {
      std::cout << "Please enter a valid description!\n";
      std::cin.clear();
      clr_buff();
    }
    tasks_edit(index, desc);
    std::cout << "Task edited with success!\n";
  }
}

int main() { // version: 0.1
  std::signal(SIGINT, [](int signal) {
    std::cout << "\nExiting..\n";
    exit(signal);
  });
  while (true) {
    print_menu();
    size_t opt;
    if (!(std::cin >> opt)) {
      if (std::cin.eof()) {
        std::cout << "\nExiting..\n";
        exit(0);
      }
    }
    switch (opt) {
    default:
      std::cout << "Enter a valid value!\n";
      break;

    case 1:
      handle_task_add();
      break;

    case 2:
      if (!tasks.size()) {
        std::cout << "Task list is empty!\n";
        break;
      }
      handle_task_pop();
      break;

    case 3:
      if (!tasks.size()) {
        std::cout << "Task list is empty!\n";
        break;
      }
      tasks_print();
      break;

    case 4:
      if (!tasks.size()) {
        std::cout << "Task list is empty!\n";
        break;
      }
      handle_task_edit();
      break;

    case 5:
      if (!tasks.size()) {
        std::cout << "Task list is empty!\n";
        break;
      }
      handle_task_conclude();
      break;

    case 0:
      std::cout << "Exiting..\n";
      exit(0);
    }
  }
}
