#include "clause.h"

namespace dpll {
enum var_stat : int8_t { kUnsat = -1, kUnknown = 0, kSat = 1 };
enum solution_stat : int8_t {
  kUnsolvable = -1,
  kSolved = 0,
  kNeedSplit = 1,
  kHasSingleCla = 2
};

class dpllSolver {
public:
  dpllSolver(){};
  dpllSolver(std::string path) {
    if (read(path)) {
      throw;
    }
  }
  ~dpllSolver(){};

  int solve();
  void show_res(size_t size);

private:
  clauseSet cla_set;
  std::vector<dpll::var_stat> results;

  int read(std::string path);
  std::tuple<int, const clause *> get_solve_stat();
  int get_next_split();
};

// Status GenResult(int *result, int *init, ALGraph *G) {
//   if (!result || !G)
//     return ERROR;
//   if (LocateVex(G, 0))
//     return ERROR;
//   for (int i = 0; i <= var_count; i++)
//     result[i] = init[i];
//   for (int i = 0; i < G->vexnum; i++) {
//     int d = G->vert[i]->data->key;
//     result[abs(d)] = d > 0 ? 1 : -1;
//   }
//   return OK;
// }
// Status PSimplify(ClaNode **head, int tar) {
//   if (!head || !tar)
//     return ERROR;
//   ClaNode *cur = *head;
//   ClaNode *prev = NULL;
//   while (cur) {
//     int status = 0;
//     for (int i = 0; i < cur->len; i++)
//       if (cur->data[i] == tar) // Match
//       {
//         status = 1; // Mark for deletion
//         if (!prev)  // Reconstruct correct links
//           *head = cur->next;
//         else
//           prev->next = cur->next;
//         DestroyCla(cur);
//         break;
//       }
//     // Redirect pointers
//     if (status) {
//       if (!prev)
//         cur = *head;
//       else
//         cur = prev->next;
//     } else {
//       prev = cur;
//       cur = cur->next;
//     }
//   }
//   return OK;
// }
// Status NSimplify(ClaNode **head, int tar) {
//   if (!head || !tar)
//     return ERROR;
//   ClaNode *cur = *head;
//   while (cur) {
//     for (int i = 0; i < cur->len; i++) {
//       if (cur->data[i] == tar) {
//         for (int j = i; j < cur->len - 1; j++)
//           cur->data[j] = cur->data[j + 1];
//         cur->len--;
//         break;
//       }
//     }
//     cur = cur->next;
//   }
//   return OK;
// }
// Status DefSimplify(ClaNode **head, int *init) {
//   if (!head || !init)
//     return ERROR;
//   for (int i = 0; i <= var_count; i++)
//     init[i] = 0;
//   ClaNode *cur = *head;
//   ClaNode *prev = NULL;
//   while (cur) {
//     if (cur->len == 1) {
//       int tar = cur->data[0];
//       PSimplify(head, tar);
//       NSimplify(head, tar * -1);
//       init[abs(tar)] = tar > 0 ? 1 : -1;
//       // cla_count--;
//       prev = NULL;
//       cur = *head;
//     } else {
//       prev = cur;
//       cur = cur->next;
//     }
//   }
//   return OK;
// }
// Status AdvSimplify(SimpSet *target, ALGraph *G, int level, int mark) {
//   if (!G || !target)
//     return ERROR;
//   int var;
//   ClaNode *cla;
//   for (int i = 0; i < target->len; i++) {
//     DeSimpSet(target, &var, &cla);
//     InsertVex(G, var, level, G->vexnum + 1);
//     if (mark == WITH_SIG_CLA) // Arc insertion required
//       for (int i = 0; i < cla->len; i++) {
//         int d = cla->data[i];
//         if (d != var)
//           InsertArc(G, var, d * -1, cla);
//       }
//   }
//   return OK;
// }
// VNode *ConflictMark(ALGraph *G, SimpSet *tar, int level) {
//   if (!G || !tar)
//     return NULL;
//   ClaNode *cla;
//   DeSimpSet(tar, NULL, &cla);
//   VNode *V = InsertVex(G, 0, level, G->vexnum + 1);
//   for (int i = 0; i < cla->len; i++) {
//     VNode *v = LocateVex(G, cla->data[i] * -1);
//     if (v)
//       InsertArc(G, 0, v->data->key, cla);
//   }
//   return V;
// }
// void *GetLatest(Queue *Q) {
//   if (!Q || !(Q->len))
//     return NULL;
//   if (Q->len == 1)
//     return DeQueue(Q);
//   QNode *prev = NULL;
//   QNode *cur = Q->head;
//   int d = ((VNode *)cur->data)->info;
//   QNode *mark = Q->head;
//   while (cur->next) {
//     int order = ((VNode *)cur->next->data)->info;
//     if (order > d) {
//       prev = cur;
//       mark = cur->next;
//       d = order;
//     }
//     cur = cur->next;
//   }
//   if (Q->head == mark)
//     Q->head = Q->head->next;
//   else if (Q->tail == mark) {
//     Q->tail = prev;
//     Q->tail->next = NULL;
//   } else
//     prev->next = mark->next;
//   void *V = mark->data;
//   free(mark);
//   Q->len--;
//   return V;
// }
// int CountLitAtLevel(Queue *cur, int level) {
//   if (!cur || level < 0 || !(cur->len))
//     return 0;
//   int count = 0;
//   QNode *t = cur->head;
//   while (t) {
//     VNode *V = (VNode *)t->data;
//     if (V->data->value == level)
//       count++;
//     t = t->next;
//   }
//   return count;
// }
// bool Resolve(ALGraph *G, VNode *tar, Queue *learnt) {
//   if (!G || !tar || !learnt)
//     return false;
//   ArcNode *arc = tar->firstarc;
//   while (arc) {
//     VNode *n = G->vert[arc->adjvex];
//     if (!InsideQueue(learnt, n))
//       EnQueue(learnt, n);
//     arc = arc->nextarc;
//   }
//   return true;
// }
// bool Analyse(ALGraph *G, ClaNode **head, int *level, VNode *confv) {
//   /*
//   Tasks of this function:
//       1.Return false when encountering unsolvable dataset;
//       2.Add a binary clause to the dataset after analysis;
//       3.Calculate a level for a possibly needed backtrace;
//       4.If back-trace needed, prune the implication graph.
//   */
//   if (!G || !head || !level)
//     return false;
//   // Task 1
//   if (!(*level))
//     return false;
//   Queue *CurLearnt = InitQueue();
//   Queue *result = InitQueue();
//   VNode *tar = NULL;
//   // Task 2
//   // Initial conflict analysis
//   for (ArcNode *arc = confv->firstarc; arc; arc = arc->nextarc)
//     EnQueue(CurLearnt, G->vert[arc->adjvex]);
//   // Analyse
//   while (CountLitAtLevel(CurLearnt, *level) + CountLitAtLevel(result, *level)
//   !=
//          1) {
//     tar = (VNode *)GetLatest(CurLearnt);
//     if (tar->data->value != *level || !(tar->firstarc)) {
//       if (!InsideQueue(result, tar))
//         EnQueue(result, tar);
//     } else
//       Resolve(G, tar, CurLearnt);
//   }
//   while (CurLearnt->len)
//     EnQueue(result, DeQueue(CurLearnt));
//   // Add on
//   ClaNode *n = InitCla();
//   n->next = *head;
//   *head = n;
//   for (int i = 0, len = result->len; i < len; i++) {
//     VNode *v = (VNode *)DeQueue(result);
//     // Task 3
//     *level = min(*level, v->data->value);
//     AddToCla(n, v->data->key * -1);
//   }
//   // Task 3 Special case
//   if (n->len == 1)
//     *level = 0;
//   // Task 4
//   for (int i = 0; i < G->vexnum; i++) {
//     if (G->vert[i]->data->value > *level) {
//       DeleteVex(G, G->vert[i]->data->key);
//       i--;
//     }
//   }
//   DestroyQueue(CurLearnt);
//   DestroyQueue(result);
//   return true;
// }
} // namespace dpll
