#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct min_max_heap {
    int *data;
    int cap;
    int size;
} min_max_heap_t;

// -- help function -- //

static inline bool is_min_layer(const int index)
{
    return (int) log2(index + 1) % 2 == 0;
}

static inline bool is_max_layer(const int index)
{
    return !is_min_layer(index);
}

static inline bool is_heap_full(min_max_heap_t *hp)
{
    return hp->cap == hp->size;
}

static inline bool is_heap_empty(min_max_heap_t *hp)
{
    return hp->size == 0;
}

// return value < 0: this node does not have grandparent
int get_grandparent_index(const int index)
{
    return index < 3 ? -1 : (index - 3) / 4;
}

// +3 to get most right gradson index
static inline int get_most_left_grandson_index(const int index)
{
    return index * 4 + 3;
}

// -3 to get most left gradson index
static inline int get_most_right_grandson_index(const int index)
{
    return get_most_left_grandson_index(index) + 3;
}

static inline int get_parent(const int index)
{
    return (index - 1) / 2;
}

static inline int get_left(const int index)
{
    return index * 2 + 1;
}

static inline int get_right(const int index)
{
    return index * 2 + 2;
}

__attribute__((nonnull)) void heap_swap_elements(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// bubble up
void heapify_up(min_max_heap_t *hp, const int index)
{
    if (index >= hp->size)
        return;

    int idx = index;
    const int data = hp->data[index];  // 使用同一個 data
    int grandparent_idx = get_grandparent_index(idx);
    const int is_min = is_min_layer(index);
    while (grandparent_idx >= 0) {
        const int grandparent_data = hp->data[grandparent_idx];
        const int is_smaller = data < grandparent_data;

        /**
         * truth table:
         * is_min  is_smaller | swap
         * --------------------------
         *    0        0      |  1
         *    0        1      |  0
         *    1        0      |  0
         *    1        1      |  1
         */
        if (!(is_min ^ is_smaller) && data != grandparent_data)
            heap_swap_elements(hp->data + idx, hp->data + grandparent_idx);
        else
            break;

        idx = grandparent_idx;
        grandparent_idx = get_grandparent_index(idx);
    }
}

// bubble down
void heapify_down(min_max_heap_t *hp, const int index)
{
    int cur_index = index;
    const int val = hp->data[index];
    const int is_min = is_min_layer(cur_index);

    // bubble down
    while (cur_index < hp->size) {
        const int left_grandson_index = get_most_left_grandson_index(cur_index);
        const int left_child_index = get_left(cur_index);

        // no child -> is leaf node
        if (left_child_index >= hp->size) {
            hp->data[cur_index] = val;
            break;
        }

        int start, end;

        // has grandson
        if (left_grandson_index < hp->size) {
            start = left_grandson_index;
            end = left_grandson_index + 3;
        }
        // has child
        else {
            start = left_child_index;
            end = left_child_index + 1;
        }
        end = end < hp->size ? end : hp->size - 1;

        int tar_index = cur_index;
        for (int i = start; i <= end; ++i) {
            const int is_smaller = hp->data[i] < hp->data[tar_index];

            /**
             * truth table:
             * is_min  is_smaller | update
             * --------------------------
             *    0        0      |  1
             *    0        1      |  0
             *    1        0      |  0
             *    1        1      |  1
             */
            if (!(is_min ^ is_smaller) && hp->data[i] != hp->data[tar_index]) {
                tar_index = i;  // update to target index
            }
        }

        if (tar_index != cur_index) {
            hp->data[cur_index] = hp->data[tar_index];
            hp->data[tar_index] = val;

            //! 如果交換到 grandson，檢查與 parent 的關係
            if (tar_index >= left_grandson_index) {
                const int parent_idx = get_parent(tar_index);
                const int parent_data = hp->data[parent_idx];
                int is_smaller = val < parent_data;
                if ((is_min ^ is_smaller) && val != parent_data) {
                    heap_swap_elements(hp->data + tar_index,
                                       hp->data + parent_idx);
                    break;
                }
            }
            //* 沒有 child 也離開
            else
                break;
        }
        //* 沒交換也離開
        else
            break;

        cur_index = tar_index;
    }
}

// -- fundamental function -- //

bool init_heap(min_max_heap_t *hp, const int cap)
{
    if (!hp || cap < 0)
        return false;

    hp->data = (int *) malloc(sizeof(int) * cap);
    if (!hp->data) {
        hp->cap = 0;
        hp->size = 0;
        return false;
    }

    hp->cap = cap;
    hp->size = 0;
    return true;
}

bool insert_heap(min_max_heap_t *hp, const int key)
{
    if (!hp || is_heap_full(hp))
        return false;  // for the case: no extra space

    hp->data[hp->size] = key;

    const int idx = hp->size++;  // last index
    const int parent_idx = get_parent(idx);
    const int is_min = is_min_layer(idx);
    const int parent_data = hp->data[parent_idx];
    const int is_smaller = key < parent_data;

    /**
     * truth table:
     * is_min  is_smaller | swap
     * --------------------------
     *    0        0      |  0
     *    0        1      |  1
     *    1        0      |  1
     *    1        1      |  0
     */
    if (is_min ^ is_smaller && key != parent_data) {
        heap_swap_elements(hp->data + idx, hp->data + parent_idx);
        heapify_up(hp, parent_idx);  //! 沒想到（忘記）的狀況，感謝教授的代碼
    } else {
        heapify_up(hp, idx);
    }
    return true;
}

bool pop_max_heap(min_max_heap_t *hp, int *ret)
{
    if (!hp || !ret || is_heap_empty(hp))
        return false;

    // get current max result as return value
    int res = hp->data[0];
    int cur_index = 0;
    for (int i = 0; i < 3 && i < hp->size; ++i) {
        if (res < hp->data[i]) {
            res = hp->data[i];
            cur_index = i;
        }
    }
    *ret = res;

    // heapify max heap
    hp->data[cur_index] = hp->data[--hp->size];
    if (!hp->size)
        return true;  // no heapify because of no element in the heap

    // bubble down
    heapify_down(hp, cur_index);
    return true;
}

bool pop_min_heap(min_max_heap_t *hp, int *ret)
{
    if (!hp || !ret || is_heap_empty(hp))
        return false;

    // get current min result as return value
    *ret = hp->data[0];

    // heapify min heap
    hp->data[0] = hp->data[--hp->size];
    if (!hp->size)
        return true;  // no heapify because of no element in the heap

    // bubble down
    heapify_down(hp, 0);
    return true;
}

void print_hp(min_max_heap_t *hp)
{
    if (!hp)
        return;

    printf("[");
    for (int i = 0; i < hp->size; ++i) {
        printf("%d ", hp->data[i]);
    }
    printf("]\n");
}

int main(void)
{
    min_max_heap_t hp;
    init_heap(&hp, 20);

    // int arr[] = {1, 8, 11, 3, 7, 2, 9, 5};
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    const int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; ++i) {
        insert_heap(&hp, arr[i]);
    }
    print_hp(&hp);

    while (1) {
        int mod;
        printf(
            "pls chose the mod (0 = insert_heap, 1 = pop_max_heap, 2 = "
            "pop_min_heap): ");
        fflush(stdout);
        scanf("%d", &mod);
        if (mod == 0) {
            int val;
            printf("pls input the insert value: ");
            fflush(stdout);
            scanf("%d", &val);

            insert_heap(&hp, val);
        } else if (mod == 1) {
            int ret;
            if (pop_max_heap(&hp, &ret)) {
                printf("got the value: %d\n", ret);
            } else {
                printf("false\n");
            }
        } else if (mod == 2) {
            int ret;
            if (pop_min_heap(&hp, &ret)) {
                printf("got the value: %d\n", ret);
            } else {
                printf("false\n");
            }
        }

        print_hp(&hp);
    }

    return 0;
}