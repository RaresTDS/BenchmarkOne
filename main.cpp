#include <gtk/gtk.h>
#include <pthread.h>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <vector>
#include <sstream>
#include <functional>

#define ARRAY_SIZE 1000000000
#define NUM_THREADS 4

long long partial_sums[NUM_THREADS];
GtkWidget *result_label;
GtkWidget *progress_bar;
GtkWidget *drawing_area;

double elapsed_time = 0;
double operations_per_second = 0;
double memory_used_mb = 0;

void on_run_benchmark(GtkWidget *widget, gpointer data);
void on_eratosthenes(GtkWidget *widget, gpointer data);
void on_prime_numbers(GtkWidget *widget, gpointer data);
void on_pi_decimals(GtkWidget *widget, gpointer data);
void on_complex_level_1(GtkWidget *widget, gpointer data);
void on_complex_level_2(GtkWidget *widget, gpointer data);
void on_matrix_multiplication(GtkWidget *widget, gpointer data);
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data);

std::vector<int> eratosthenes(int n) {
    std::vector<bool> is_prime(n + 1, true);
    std::vector<int> primes;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}


std::string calculate_pi(int n) {
    std::ostringstream pi_stream;
    pi_stream.precision(n);
    pi_stream << std::fixed;

    double pi = 0.0;
    for (int k = 0; k < n; ++k) {
        pi += (pow(-1, k) / (2 * k + 1)) * 4;
    }
    pi_stream << pi;
    return pi_stream.str();
}

void run_benchmark(const char *task_name, const std::function<void()> &task, size_t operations) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    task();

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    operations_per_second = operations / elapsed_time;
    memory_used_mb = (ARRAY_SIZE * sizeof(long long)) / (1024.0 * 1024.0);

    char result[512];
    snprintf(result, sizeof(result),
             "%s\nExecution time: %.3f seconds\nOperations: %zu\nPerformance: %.2f OPS\nMemory used: %.2f MB",
             task_name, elapsed_time, operations, operations_per_second, memory_used_mb);
    gtk_label_set_text(GTK_LABEL(result_label), result);

    gtk_widget_queue_draw(drawing_area);
}

void on_run_benchmark(GtkWidget *widget, gpointer data) {
    run_benchmark("Benchmark - Run Benchmark", []() {
        long long sum = 0;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            sum += sqrt(i) * pow(i, 2);
        }
    }, ARRAY_SIZE);
}

void matrix_multiplication(int size) {
    std::vector<std::vector<int>> matrixA(size, std::vector<int>(size, 1));
    std::vector<std::vector<int>> matrixB(size, std::vector<int>(size, 1));
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void on_matrix_multiplication(GtkWidget *widget, gpointer data) {
    const int matrix_size = 2000;
    run_benchmark("Benchmark - Multiplicarea Matricelor", [=]() {
        matrix_multiplication(matrix_size);
    }, matrix_size * matrix_size * matrix_size);
}

void on_eratosthenes(GtkWidget *widget, gpointer data) {
    run_benchmark("Benchmark - Ciurul lui Eratostene", []() {
        auto primes = eratosthenes(ARRAY_SIZE);
    }, ARRAY_SIZE);
}

void on_pi_decimals(GtkWidget *widget, gpointer data) {
    run_benchmark("Benchmark - Zecimalele lui Pi", []() {
        std::string pi = calculate_pi(500000);
    }, ARRAY_SIZE);
}

void on_complex_level_1(GtkWidget *widget, gpointer data) {
    run_benchmark("Benchmark - Complex Nivel 1", []() {
        long long sum = 0;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            sum += i * i - sqrt(i) * sin(i);
        }
    }, ARRAY_SIZE);
}

void on_complex_level_2(GtkWidget *widget, gpointer data) {
    run_benchmark("Benchmark - Complex Nivel 2", []() {
        long long sum = 0;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            sum += pow(i, 3) * log(i + 1) - sin(i);
        }
    }, ARRAY_SIZE);
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
    cairo_paint(cr);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 1);

    cairo_move_to(cr, 50, 150);
    cairo_line_to(cr, 280, 150);
    cairo_stroke(cr);

    cairo_move_to(cr, 50, 50);
    cairo_line_to(cr, 50, 200);
    cairo_stroke(cr);

    cairo_set_font_size(cr, 10);
    cairo_move_to(cr, 35, 155);
    cairo_show_text(cr, "0");

    cairo_move_to(cr, 35, 100);
    cairo_show_text(cr, "Time (s)");

    cairo_move_to(cr, 35, 80);
    cairo_show_text(cr, "(seconds)");

    cairo_move_to(cr, 270, 160);
    cairo_show_text(cr, "Performance (OPS)");

    cairo_set_source_rgb(cr, 0.2, 0.4, 0.8);
    cairo_set_line_width(cr, 3);
    cairo_move_to(cr, 50, 150);
    cairo_line_to(cr, 250, 150 - (elapsed_time * 10));
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 0.8, 0.2, 0.2);
    cairo_set_line_width(cr, 3);
    cairo_move_to(cr, 50, 150);
    cairo_line_to(cr, 250, 150 - (operations_per_second * 0.00001));
    cairo_stroke(cr);

    return FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Benchmark One");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_vbox);

    GtkWidget *button = gtk_button_new_with_label("Basic Level");
    g_signal_connect(button, "clicked", G_CALLBACK(on_run_benchmark), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), button, FALSE, FALSE, 0);

    GtkWidget *complex1_button = gtk_button_new_with_label("Complex Nivel 1");
    g_signal_connect(complex1_button, "clicked", G_CALLBACK(on_complex_level_1), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), complex1_button, FALSE, FALSE, 0);

    GtkWidget *complex2_button = gtk_button_new_with_label("Complex Nivel 2");
    g_signal_connect(complex2_button, "clicked", G_CALLBACK(on_complex_level_2), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), complex2_button, FALSE, FALSE, 0);

    GtkWidget *eratosthenes_button = gtk_button_new_with_label("Ciurul lui Eratostene");
    g_signal_connect(eratosthenes_button, "clicked", G_CALLBACK(on_eratosthenes), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), eratosthenes_button, FALSE, FALSE, 0);

    GtkWidget *pi_button = gtk_button_new_with_label("Zecimalele lui PI");
    g_signal_connect(pi_button, "clicked", G_CALLBACK(on_pi_decimals), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), pi_button, FALSE, FALSE, 0);


    GtkWidget *matrix_button = gtk_button_new_with_label("Multiplicarea Matricelor");
    g_signal_connect(matrix_button, "clicked", G_CALLBACK(on_matrix_multiplication), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), matrix_button, FALSE, FALSE, 0);


    result_label = gtk_label_new("Press a button to start");
    gtk_box_pack_start(GTK_BOX(main_vbox), result_label, FALSE, FALSE, 0);

    progress_bar = gtk_progress_bar_new();
    gtk_box_pack_start(GTK_BOX(main_vbox), progress_bar, FALSE, FALSE, 0);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 300, 200);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), nullptr);
    gtk_box_pack_start(GTK_BOX(main_vbox), drawing_area, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}