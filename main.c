#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node {
    char inf[256];
    int priority;
    struct node* next;
};

struct node* stack_top = NULL;

void stack_push(const char* name) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    strcpy(p->inf, name);
    p->priority = 0;
    p->next = stack_top;
    stack_top = p;
    printf("[Стек] Добавлен (push): %s\n", name);
}

void stack_pop() {
    if (stack_top == NULL) {
        printf("[Стек] Ошибка: стек пуст!\n");
        return;
    }
    struct node* tmp = stack_top;
    printf("[Стек] Извлечен (pop): %s\n", tmp->inf);
    stack_top = stack_top->next;
    free(tmp);
}

void stack_review() {
    struct node* curr = stack_top;
    printf("Содержимое стека (от вершины вниз):\n");
    while (curr != NULL) {
        printf(" -> %s\n", curr->inf);
        curr = curr->next;
    }
}

void stack_clear() {
    while (stack_top != NULL) {
        struct node* tmp = stack_top;
        stack_top = stack_top->next;
        free(tmp);
    }
}

struct node* q_head = NULL;
struct node* q_tail = NULL;

void queue_enqueue(const char* name) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    strcpy(p->inf, name);
    p->priority = 0;
    p->next = NULL;

    if (q_head == NULL) {
        q_head = q_tail = p;
    }
    else {
        q_tail->next = p;
        q_tail = p;
    }
    printf("[Очередь] Добавлен в хвост: %s\n", name);
}

void queue_dequeue() {
    if (q_head == NULL) {
        printf("[Очередь] Ошибка: очередь пуста!\n");
        return;
    }
    struct node* tmp = q_head;
    printf("[Очередь] Обслужен (извлечен): %s\n", tmp->inf);
    q_head = q_head->next;
    if (q_head == NULL) q_tail = NULL;
    free(tmp);
}

void queue_review() {
    struct node* curr = q_head;
    printf("Содержимое очереди (от головы к хвосту):\n");
    while (curr != NULL) {
        printf(" -> %s\n", curr->inf);
        curr = curr->next;
    }
}

void queue_clear() {
    while (q_head != NULL) {
        struct node* tmp = q_head;
        q_head = q_head->next;
        free(tmp);
    }
    q_tail = NULL;
}

struct node* pq_head = NULL;

void pq_enqueue(const char* name, int priority) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    strcpy(p->inf, name);
    p->priority = priority;
    p->next = NULL;

    if (pq_head == NULL || priority > pq_head->priority) {
        p->next = pq_head;
        pq_head = p;
    }
    else {
        struct node* curr = pq_head;
        while (curr->next != NULL && curr->next->priority >= priority) {
            curr = curr->next;
        }
        p->next = curr->next;
        curr->next = p;
    }
    printf("[Приор. очередь] Добавлен: %s (Приоритет: %d)\n", name, priority);
}

void pq_dequeue() {
    if (pq_head == NULL) {
        printf("[Приор. очередь] Ошибка: очередь пуста!\n");
        return;
    }
    struct node* tmp = pq_head;
    printf("[Приор. очередь] Извлечен макс. приоритет: %s (Приоритет: %d)\n", tmp->inf, tmp->priority);
    pq_head = pq_head->next;
    free(tmp);
}

void pq_find(const char* name) {
    struct node* curr = pq_head;
    int pos = 1;
    while (curr != NULL) {
        if (strcmp(curr->inf, name) == 0) {
            printf("[Приор. очередь] Элемент '%s' найден на позиции %d (Приоритет: %d)\n", name, pos, curr->priority);
            return;
        }
        curr = curr->next;
        pos++;
    }
    printf("[Приор. очередь] Элемент '%s' не найден.\n", name);
}

void pq_del(const char* name) {
    if (pq_head == NULL) return;

    struct node* curr = pq_head;
    struct node* prev = NULL;

    if (strcmp(curr->inf, name) == 0) {
        pq_head = curr->next;
        free(curr);
        printf("[Приор. очередь] Элемент '%s' успешно удален.\n", name);
        return;
    }

    while (curr != NULL && strcmp(curr->inf, name) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL) {
        prev->next = curr->next;
        free(curr);
        printf("[Приор. очередь] Элемент '%s' успешно удален.\n", name);
    }
    else {
        printf("[Приор. очередь] Элемент '%s' для удаления не найден.\n", name);
    }
}

void pq_review() {
    struct node* curr = pq_head;
    printf("Содержимое приоритетной очереди (по убыванию приоритета):\n");
    while (curr != NULL) {
        printf(" -> %s (Приоритет: %d)\n", curr->inf, curr->priority);
        curr = curr->next;
    }
}

void pq_clear() {
    while (pq_head != NULL) {
        struct node* tmp = pq_head;
        pq_head = pq_head->next;
        free(tmp);
    }
}

void run_demo() {
    printf("\n--- АВТОМАТИЧЕСКОЕ ТЕСТИРОВАНИЕ ---\n");

    printf("\n1. СТЕК (LIFO)\n");
    stack_push("Документ_1");
    stack_push("Документ_2");
    stack_push("Документ_3");
    stack_review();
    stack_pop();
    stack_review();

    printf("\n2. ОЧЕРЕДЬ (FIFO)\n");
    queue_enqueue("Клиент_А");
    queue_enqueue("Клиент_Б");
    queue_enqueue("Клиент_В");
    queue_review();
    queue_dequeue();
    queue_review();

    printf("\n3. ПРИОРИТЕТНАЯ ОЧЕРЕДЬ\n");
    pq_enqueue("Фон", 1);
    pq_enqueue("Крит_ошибка", 10);
    pq_enqueue("Срочно", 8);
    pq_enqueue("БД_запрос1", 5);
    pq_enqueue("БД_запрос2", 5);
    pq_review();

    printf("\nПоиск и удаление:\n");
    pq_find("Срочно");
    pq_del("Срочно");
    pq_review();

    printf("\nИзвлечение всех по приоритету:\n");
    while (pq_head != NULL) pq_dequeue();

    printf("\n--- ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ ---\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    char name[256];
    int priority;

    while (1) {
        printf("\n=====================================\n");
        printf("1. Запустить демо-тест\n");
        printf("2. Стек: push\n");
        printf("3. Стек: pop\n");
        printf("4. Стек: review\n");
        printf("5. Очередь: enqueue\n");
        printf("6. Очередь: dequeue\n");
        printf("7. Очередь: review\n");
        printf("8. Приор. очередь: добавить (имя и приоритет)\n");
        printf("9. Приор. очередь: извлечь максимум\n");
        printf("10. Приор. очередь: найти по имени\n");
        printf("11. Приор. очередь: удалить по имени\n");
        printf("12. Приор. очередь: review\n");
        printf("0. Выход\n");
        printf("=====================================\n");
        printf("Выбор: ");

        if (scanf("%d", &choice) != 1) break;

        if (choice == 0) break;
        else if (choice == 1) run_demo();
        else if (choice == 2) { printf("Имя: "); scanf("%255s", name); stack_push(name); }
        else if (choice == 3) stack_pop();
        else if (choice == 4) stack_review();
        else if (choice == 5) { printf("Имя: "); scanf("%255s", name); queue_enqueue(name); }
        else if (choice == 6) queue_dequeue();
        else if (choice == 7) queue_review();
        else if (choice == 8) {
            printf("Имя: "); scanf("%255s", name);
            printf("Приоритет: "); scanf("%d", &priority);
            pq_enqueue(name, priority);
        }
        else if (choice == 9) pq_dequeue();
        else if (choice == 10) { printf("Имя: "); scanf("%255s", name); pq_find(name); }
        else if (choice == 11) { printf("Имя: "); scanf("%255s", name); pq_del(name); }
        else if (choice == 12) pq_review();
    }

    stack_clear();
    queue_clear();
    pq_clear();
    return 0;
}
