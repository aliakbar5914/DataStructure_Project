# GitLite – A Simplified Version Control System (C++)

**GitLite** is a lightweight, Git-inspired version control system implemented in **C++** using advanced data structures like **AVL Trees**. It allows users to initialize repositories from CSV data, manage commits, handle branches, and switch between them — all through a command-line interface.

---

## Features

### Repository Initialization
- Load and parse large **CSV files**.
- Choose a **tree structure**: AVL
- Select the column to use as the key.
- Each tree node is stored in a **separate file** for scalability.
- Files are named after the key values, maintaining a flat file hierarchy.

### Data Structures
- **AVL Tree**: Automatically balances during insertion/deletion for efficient access.
- File-based nodes: Only necessary files are loaded into memory to optimize performance.

### Commit System
- Add/Delete/Update files in the repository.
- Each change is associated with a **commit message** and **timestamp**.
- Commit logs are stored in `commit.txt` per branch.

### Branching and Switching
- Create new branches stored as subfolders.
- Each branch maintains its **own tree state** and commit history.
- **Switch** between branches using a menu-based interface.

### Merge Branches
- Merge one branch into another, combining data trees.
- Branch states are updated upon successful merge.

### Hashing for Fast Lookup
- Each file is hashed and indexed using a **custom hash function**.
- Supports display and deletion through hash-based access.

---

