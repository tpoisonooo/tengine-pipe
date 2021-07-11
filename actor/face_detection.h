#pragma once
#include "../graph/node.h"
#include <opencv2/opencv.hpp>
#include <c_api.h>
#include "common/tengine_operations.h"

namespace pipe{

struct Box
{
    int x0;
    int y0;
    int x1;
    int y1;
    int class_idx;
    float score;
};

class FaceDetection: public Node<Param<cv::Mat>, Param<cv::Mat>> {
public:

    FaceDetection(std::string model_path) {
        /* inital tengine */
        init_tengine();
        fprintf(stderr, "tengine-lite library version: %s\n", get_tengine_version());
        m_graph = create_graph(NULL, "tengine", model_path.c_str());
        if (m_graph == nullptr) {
            fprintf(stderr, "create graph failed\n");
        }
    }

    void exec() override {
        cv::Mat mat;
        auto suc = input<0>()->pop(mat);
        if (not suc or mat.empty()) {
            return;
        }

        int repeat_count = DEFAULT_REPEAT_COUNT;
        int num_thread = DEFAULT_THREAD_COUNT;
        char* model_file = NULL;
        char* image_file = NULL;
        int img_h = 300;
        int img_w = 300;
        float mean[3] = {127.5f, 127.5f, 127.5f};
        float scale[3] = {0.007843f, 0.007843f, 0.007843f};
        float show_threshold = 0.5f;
        
        /* set runtime options */
        struct options opt;
        opt.num_thread = 4;
        opt.cluster = TENGINE_CLUSTER_ALL;
        opt.precision = TENGINE_MODE_FP32;
        opt.affinity = 0;

        /* set the input shape to initial the graph, and prerun graph to infer shape */
        int img_size = img_h * img_w * 3;
        int dims[] = {1, 3, img_h, img_w};    // nchw
        float* input_data = ( float* )malloc(img_size * sizeof(float));

        tensor_t input_tensor = get_graph_input_tensor(graph, 0, 0);
        if (input_tensor == NULL)
        {
            fprintf(stderr, "Get input tensor failed\n");
            return -1;
        }

        if (set_tensor_shape(input_tensor, dims, 4) < 0)
        {
            fprintf(stderr, "Set input tensor shape failed\n");
            return -1;
        }

        if (set_tensor_buffer(input_tensor, input_data, img_size * 4) < 0)
        {
            fprintf(stderr, "Set input tensor buffer failed\n");
            return -1;
        }    

        /* prerun graph, set work options(num_thread, cluster, precision) */
        if (prerun_graph_multithread(graph, opt) < 0)
        {
            fprintf(stderr, "Prerun graph failed\n");
            return -1;
        }

        /* prepare process input data, set the data mem to input tensor */
        get_input_data(image_file, input_data, img_h, img_w, mean, scale);

    }

    ~FaceDetection() {
    }

private:
    graph_t m_graph;
};

}