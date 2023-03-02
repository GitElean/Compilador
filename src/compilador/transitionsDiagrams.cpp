//clase para graficar los distintos automatas y lenguajes
#include <iostream>
#include <fstream>
#include <string>

#include <graphviz/gvc.h>

class GraphvizTransitionDiagram {
public:
    GraphvizTransitionDiagram(const std::string& graphviz_output) {
        // Inicializa Graphviz
        GVC_t* gvc = gvContext();
        if (!gvc) {
            throw std::runtime_error("Error al iniciar graphviz");
        }

        // Parsea la entrada
        Agraph_t* graph = agmemread(graphviz_output.c_str());
        if (!graph) {
            throw std::runtime_error("Error al parsear.");
        }

        // Genera el layout del grafo
        if (gvLayout(gvc, graph, "dot") != 0) {
            throw std::runtime_error("Error al generar el grafo.");
        }

        // Create a PNG image of the graph
        char* format = "png";
        unsigned char* image_data = nullptr;
        unsigned int image_size = 0;
        if (gvRenderData(gvc, graph, format, &image_data, &image_size) != 0) {
            throw std::runtime_error("Error al generar la imagen.");
        }

        // Write the PNG image to a file
        std::ofstream image_file("diagrama_de_transicion.png", std::ios::binary);
        if (!image_file) {
            throw std::runtime_error("Error al abrir la imagen.");
        }
        image_file.write(reinterpret_cast<const char*>(image_data), image_size);
        image_file.close();

        // Cleanup
        gvFreeRenderData(image_data);
        gvFreeLayout(gvc, graph);
        agclose(graph);
        gvFreeContext(gvc);
    }
};