import os
import re
import json
from pyvis.network import Network
import emerge as eg


def find_cmake_files(root_dir, ignore_dirs):
    cmake_files = []
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Remove ignored directories from search
        dirnames[:] = [
            d for d in dirnames if os.path.join(dirpath, d) not in ignore_dirs
        ]
        for filename in filenames:
            if filename == "CMakeLists.txt":
                cmake_files.append(os.path.join(dirpath, filename))
    return cmake_files


def extract_linked_targets(file_path):
    with open(file_path, "r") as file:
        content = file.read()

    # Regex to find target_link_libraries calls
    link_pattern = re.compile(
        r"target_link_libraries\(\s*([\w:]+)\s+(.*?)\)", re.DOTALL
    )
    alias_pattern = re.compile(r"add_library\(\s*([\w:]+)\s+ALIAS\s+([\w:]+)\s*\)")

    # Find alias definitions
    alias_matches = alias_pattern.findall(content)
    aliases = {target: alias for alias, target in alias_matches}

    # Find target link libraries
    matches = link_pattern.findall(content)
    targets = {}

    for target, libs in matches:
        public_libs = re.findall(r"PUBLIC\s+([\w\s:]+)", libs)
        private_libs = re.findall(r"PRIVATE\s+([\w\s:]+)", libs)

        if target not in targets:
            targets[target] = {"PUBLIC": [], "PRIVATE": []}

        targets[target]["PUBLIC"].extend(public_libs[0].split() if public_libs else [])
        targets[target]["PRIVATE"].extend(
            private_libs[0].split() if private_libs else []
        )

    # Replace target names with alias names
    for target, alias in aliases.items():
        if target in targets:
            targets[alias] = targets.pop(target)

    return targets


def get_deep_deps(graph: dict[str, dict[str, list]], target: str) -> set[str]:
    result_public_list = set()
    if target not in graph:
        return result_public_list
    for linked in graph[target]["PUBLIC"]:
        result_public_list.add(linked)
        result_public_list.update(get_deep_deps(graph, linked))
    return result_public_list


def build_linked_graph(cmake_files, check_public=False):
    linked_graph: dict[str, list] = dict()
    if check_public:
        temp_dependency_graph: dict[str, dict[str, list]] = dict()
        for file in cmake_files:
            targets = extract_linked_targets(file)
            for target, linked in targets.items():
                if target not in temp_dependency_graph:
                    temp_dependency_graph[target] = {"PUBLIC": [], "PRIVATE": []}
                temp_dependency_graph[target]["PUBLIC"].extend(linked["PUBLIC"])
                temp_dependency_graph[target]["PRIVATE"].extend(linked["PRIVATE"])
        # temp_dependency_graph = {
        #     "0": {"PUBLIC": [], "PRIVATE": []},
        #     "1": {"PUBLIC": ["3"], "PRIVATE": ["2"]},
        #     "2": {"PUBLIC": [], "PRIVATE": ["0"]},
        #     "3": {"PUBLIC": ["4"], "PRIVATE": []},
        #     "4": {"PUBLIC": ["5"], "PRIVATE": []},
        #     "5": {"PUBLIC": [], "PRIVATE": []},
        # }
        for target_dep, _ in temp_dependency_graph.items():
            linked_graph[target_dep] = list(
                get_deep_deps(temp_dependency_graph, target_dep)
            )
            linked_graph[target_dep].extend(
                temp_dependency_graph[target_dep]["PRIVATE"]
            )
    else:
        for file in cmake_files:
            targets = extract_linked_targets(file)
            for target, linked in targets.items():
                if target not in linked_graph:
                    linked_graph[target] = []
                linked_graph[target].extend(linked["PUBLIC"])
                linked_graph[target].extend(linked["PRIVATE"])
    return linked_graph


def visualize_graph_pyvi(graph_dict):
    # Create a pyvis network
    net = Network(height="1080px", directed=True, notebook=True)

    all_nodes = set()
    # Add nodes and edges to the network
    for node, neighbors in graph_dict.items():
        all_nodes.add(node)
        all_nodes.update(neighbors)
    for node in all_nodes:
        net.add_node(node, label=node)

    for node, neighbors in graph_dict.items():
        for neighbor in neighbors:
            try:
                net.add_edge(node, neighbor)
            except AssertionError as e:
                print(e)
    # Show the graph
    net.show("graph.html")


def main():
    root_dir = "."  # Set the root directory of your CMake project
    ignore_dirs = {
        # "./libs",
        # "./src/external",
        # "./.build",
    }  # Update with paths to ignore

    cmake_files = find_cmake_files(root_dir, ignore_dirs)
    linked_graph = build_linked_graph(cmake_files, check_public=True)

    # Output JSON
    output_json = json.dumps(linked_graph, indent=4)
    print(output_json)

    # output_dict = dict()
    # for key in linked_graph.keys():
    #     output_dict[key] = linked_graph[key]["PRIVATE"] + linked_graph[key]["PUBLIC"]
    # print(output_dict)

    visualize_graph_pyvi(linked_graph)


if __name__ == "__main__":
    main()
