typedef struct vertex_s
{
    char *name;
    struct edge_s *edges;
    size_t num_edges;
} vertex_t;

typedef struct edge_s
{
    vertex_t *vertex;
    int weight;
} edge_t;

typedef struct graph_s
{
    vertex_t **vertices;
    size_t num_vertices;
} graph_t;
