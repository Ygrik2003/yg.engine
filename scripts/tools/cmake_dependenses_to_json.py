import os
import re
import json

def find_cmake_files(root_dir, ignore_dirs):
    cmake_files = []
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Remove ignored directories from search
        dirnames[:] = [d for d in dirnames if os.path.join(dirpath, d) not in ignore_dirs]
        for filename in filenames:
            if filename == 'CMakeLists.txt':
                cmake_files.append(os.path.join(dirpath, filename))
    return cmake_files

def extract_linked_targets(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    # Regex to find target_link_libraries calls
    link_pattern = re.compile(r'target_link_libraries\(\s*([\w:]+)\s+(.*?)\)', re.DOTALL)
    alias_pattern = re.compile(r'add_library\(\s*([\w:]+)\s+ALIAS\s+([\w:]+)\s*\)')

    # Find alias definitions
    alias_matches = alias_pattern.findall(content)
    aliases = {target: alias for alias, target in alias_matches}

    # Find target link libraries
    matches = link_pattern.findall(content)
    targets = {}

    for target, libs in matches:
        public_libs = re.findall(r'PUBLIC\s+([\w\s:]+)', libs)
        private_libs = re.findall(r'PRIVATE\s+([\w\s:]+)', libs)

        if target not in targets:
            targets[target] = {'PUBLIC': [], 'PRIVATE': []}

        targets[target]['PUBLIC'].extend(public_libs[0].split() if public_libs else [])
        targets[target]['PRIVATE'].extend(private_libs[0].split() if private_libs else [])

    # Replace target names with alias names
    for target, alias in aliases.items():
        if target in targets:
            targets[alias] = targets.pop(target)

    return targets

def build_linked_graph(cmake_files):
    linked_graph = {}
    for file in cmake_files:
        targets = extract_linked_targets(file)
        for target, libs in targets.items():
            if target not in linked_graph:
                linked_graph[target] = {'PUBLIC': [], 'PRIVATE': []}
            linked_graph[target]['PUBLIC'].extend(libs['PUBLIC'])
            linked_graph[target]['PRIVATE'].extend(libs['PRIVATE'])
    return linked_graph

def main():
    root_dir = '.'  # Set the root directory of your CMake project
    ignore_dirs = {'./libs', './src/external', './.build'}  # Update with paths to ignore

    cmake_files = find_cmake_files(root_dir, ignore_dirs)
    linked_graph = build_linked_graph(cmake_files)
    # Output JSON
    output_json = json.dumps(linked_graph, indent=4)
    print(output_json)

if __name__ == '__main__':
    main()
