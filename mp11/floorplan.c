#include "floorplan.h"

/* Intro paragraph:
 *
 * To implement the init_slicing_tree function, I first checked for the base case that the node to be inserted
 * is the last node. In this case, simply create the node, assign the correct data accordingly, and return a pointer
 * to this node. If not, then create an internal node to attach the new node, so create an internal node and assign 
 * the data accordingly. Then, attach the new node to the right of the newly made internal node. Finally, recursively
 * call on itself, using the new internal node as the parent argument, and incremented index as n argument. The pointer
 * this recursive call returns is a pointer to the root of the new subtree made, so the left pointer of the new 
 * internal node is set to this. Finally, return a pointer to the new internal node.
 * 
 * To implement the is_leaf_node function, simply check if all its children is NULL and return the result.
 * 
 * To implement the is_internal_node function, we can use the is_leaf_node function and simply take the invert of the 
 * result, since a node is either a leaf or an internal node.
 * 
 * To impelement the is_in_subtree function, check if we can follow 0 or more parent links of b to reach a. If we can,
 * then that means b resides at the subtree rooted at a.
 * 
 * To implement the rotate function, simply swap the height and width of the module of the leaf node.
 * 
 * To implement the recut function, simply change the cutline of the internal node to the opposite of it was. In
 * other words, if it was V, change it to H. If it was H, change it to V.
 * 
 * To implement the swap_module function, simply swap whatever the module pointers of both nodes were pointing to.
 * To do this, a temp pointer may be used to keep a pointer pointing to one module while the swap is done.
 * 
 * To implement the swap_topology function, first get the parents of both nodes. Then, set the parent of a to point to b, 
 * using whichever left or right pointer was originally pointing to a. After, adjust b's parent pointer to point to the
 * original parent of a. Similarly for b, set the parent of b to point to a, using whichever left or right pointer was 
 * originally pointing to b. After, adjust a's parent pointer to point to the original parent of b.
 * 
 * To implement the get_expression function, fix the postfix_traversal function. To do this, recall that postorder is 
 * visiting the nodes on the left, right, and current node, in that order. So, we can first call the function recursively
 * for the left and right nodes, in that order, of the current node, without changing the nth argument. Then, after these 
 * calls we can handle the node case by first checking if the node is an internal node. If so, update the cutline of the
 * current element in the expression array. If not, update the module of the current element in the expression array. 
 * Finally, increment the value of nth, since we have processed one node.
 * 
 * To implement the get_total_resource function, I decided to traverse the tree in an preorder fashion, since this way we 
 * can avoid extra recursive calls with only null. To handle the base case, if the node is null, simply return 0. We can 
 * then check if the node is a leaf node, in which case we can return its resource value, since we are assured it has no 
 * children. If not, then we have two recursive calls to find the total resource of the subtree rooted at the left and 
 * right nodes of the current node. Finally, we can return the sum of the total resource returned by our two recursive calls.
 * 
 * Partners: htd2, clegras2
 */

// Global variables. The global variables will be effectice after the input has been parsed
// by calling the procedure read_module.
int num_modules;                                            // # of input modules.
module_t* modules;                                          // Array for modules.

// Procedure: floorplan
// The major procedure of the floorplan. The procedure concists of the following major steps:
// - initialize the slicing tree.
// - print the information of the slicing tree.
// - perform the optimization process.
void floorplan(const char file[]) {
  
  /*printf("\n********************************** MP11 **********************************\n");
  // Read the modules from the given input file.
  read_modules(file);
  // Initialize the slicing tree. You can replace the function init_slicing_tree with the function
  // challenge_init_slicing_tree if you accomplish the challenge implementation.
  node_t* root = init_slicing_tree(NULL, 0);
  int num_nodes = (num_modules << 1) - 1;
  printf("Initial slicing tree: Root=%p, num_nodes=%d, num_modules=%d\n", root, num_nodes, num_modules);
  // Obtain the expression of the initial slicing tree. 
  expression_unit_t* expression = (expression_unit_t*)calloc(num_nodes, sizeof(expression_unit_t));
  get_expression(root, num_nodes, expression);
  printf("Initial expression: ");
  pnt_expression(expression, num_nodes);     
  double area = packing(expression, num_nodes);
  printf("Initial area: %.5e\n", area);
  draw_modules("init.png");
  free(expression);
  // Perform the optimization process.
  printf("Perform optimization...\n");
  area = optimize(root, num_nodes);
  pnt_modules();
  printf("Packing area = %.5e (has overlapped? %d (1:yes, 0:no))\n", area, is_overlapped());
  // Output your floorplan.
  printf("Draw floorplan to %s\n", outfile);
  draw_modules(outfile);
  
  printf("********************************** END ***********************************\n");*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS/PROCEDURES YOU HAVE TO FINISH.                                                      //
///////////////////////////////////////////////////////////////////////////////////////////////////



// Function: is_leaf_node
// Return 1 if the given slicing tree node is a leave node, and 0 otherwise.
int is_leaf_node(node_t* ptr) {
  // TODO: (remember to modify the return value appropriately)
  return (ptr->left == NULL && ptr->right==NULL);
}

// Function: is_internal_node
// Return 1 if the given slicing tree node is an internal node, and 0 otherwise.
int is_internal_node(node_t* ptr) {
  // TODO: (remember to modify the return value appropriately)
  // A node is an internal node if it is not a leaf node, if we use the convention root can be an internal node
  return (!is_leaf_node(ptr));
}

// Function: is_in_subtree
// Return 1 if the given subtree rooted at node 'b' resides in the subtree rooted at node 'a'.
int is_in_subtree(node_t* a, node_t* b) {
  // TODO: (remember to modify the return value appropriately)
  // If we can follow 0 or more parent links of b to reach a, then return 1
  // Else, the subtree rooted at 'b' is not in the subtree rooted at 'a' and return 0

  // Check if b is equal to a, meaning we have followed the parent link and reached a
  if (a == b) return 1;
  // This also takes care of the fact that a null subtree is a child subtree of a null subtree

  // Check if b is NULL, meaning we can't go further up 
  // So, return 0
  if (b == NULL) return 0;

  // Follow the next parent link of b
  return is_in_subtree(a, b->parent);

}

// Procedure: rotate
// Rotate a module from a given leave node of the slicing tree by 90 degree. That is, the height 
// and the width of the modules are swapped.
void rotate(node_t* ptr) {
  // TODO: 

  // Check for null like how you check for bombs at airport security: always and everywhere
  if (ptr == NULL || ptr->module == NULL) return;

  // Verify that the node is a leaf node
  if (!is_leaf_node(ptr)) return;

  int tempHeight = ptr->module->h;
  ptr->module->h = ptr->module->w;
  ptr->module->w = tempHeight;
}

// Procedure: recut
// Change the cutline of a module in a given internal node of the slicing tree. 
// If the original cutline is a vertical cutline, the resulting cutline should be changed to 
// horizontal and vice versa. 
void recut(node_t* ptr) {
  if (!is_internal_node(ptr)) return;
  assert(ptr->module == NULL && ptr->cutline != UNDEFINED_CUTLINE);

  // TODO:

  // Checks not necessary because of assert above, but are nice to include
  // Again check for null, just like how you check for bombs at airport security: always and everywhere
  if (ptr == NULL) return;

  // Perform the RECUT...Greyworm and the unsullied: *sweating intensifies*
  ptr->cutline = (ptr->cutline == V) ? H : V;
}

// Procedure: swap_module
// Swap the two modules between two given leave nodes in the slicing tree.
void swap_module(node_t* a, node_t* b) {
  if(!is_leaf_node(a) || !is_leaf_node(b)) return;
  assert(a->module != NULL && a->cutline == UNDEFINED_CUTLINE);
  assert(b->module != NULL && b->cutline == UNDEFINED_CUTLINE);

  // TODO:
  // Above has already verified that both nodes are leaves, and both nodes module is not null,
  // (assuming a and b are not NULL themselves), and that both nodes cutline is undefined
  // All that is left to do is swap pointer values

  module_t* tmp = a->module;
  a->module = b->module;
  b->module = tmp;
}

// Procedure: swap_topology
// Swap the topology of two subtrees rooted at two given nodes of the slicing tree. 
// The procedure applies "is_in_subtree" first to tell if any of the subtree belongs
// to a part of the other. 
void swap_topology(node_t* a, node_t* b) {
  if(a == NULL || b == NULL) return;
  if(a->parent == NULL || b->parent == NULL) return;
  if(is_in_subtree(a, b) || is_in_subtree(b, a)) return;
  assert(a->parent != NULL && b->parent != NULL);
 
  // TODO:
  // Above has already verified all the edge cases we need to cover
  // All that is left is to swap the two subtrees rooted at a and b

  // Get parent of both nodes
  node_t* aParent = a->parent;
  node_t* bParent = b->parent;

  // Put b where a was
  // Modify a's parent to point to b
  if (aParent->left == a) {
    aParent->left = b;
  } else {
    aParent->right = b;
  }
  // Modify b's parent pointer to point to the new parent
  b->parent = aParent;

  // Now, put a to where b is
  // Modify b's parent to point to a
  if (bParent->left == b) {
    bParent->left = a;
  } else {
    bParent->right = a;
  }
  // Modify a's parent pointer to point to the new parent
  a->parent = bParent;

}

// Procedure: get_expression
// Perform the post-order traversal on the given slicing tree and stores the polish expression
// into the given expression array. You should assume the expression array is pre-allocated with
// size N. In other words, you don't have to perform dynamic memory allocation. In fact, there
// is no need for you to add any code here, but it would be better if you can understand the 
// details of this procedure especially the last two lines where the procedure postfix_traversal
// is called internally to obtain the expression.
void get_expression(node_t* root, int N, expression_unit_t* expression) {
  int i;
  // Clear the expression.
  for(i=0; i<N; ++i) {
    expression[i].module = NULL;
    expression[i].cutline = UNDEFINED_CUTLINE;
  }

  // Obtain the expression using the postfix traversal.
  int nth = 0;
  postfix_traversal(root, &nth, expression);
}

// Procedure: postfix_traversal
// Perform the postfix traversal on the slicing tree and store the corresponding polish expression
// to the given expression array. You should use the pointer "nth" to find out the index of the
// expression array and write the data accordingly. Notice that the expression array is a sequence
// of expression units which could be either a module pointer or the cutline type. If the module
// pointer exists in the expression unit, you should set the corresponding cutline type to 
// "UNDEFINED_CUTLINE". On the other hand, if the expression unit is a cutline type, you should 
// assign NULL to the corresponding module pointer.
void postfix_traversal(node_t* ptr, int* nth, expression_unit_t* expression) {
  
  if(ptr == NULL) return;

  // TODO:

  // Base case handled above, so handle recursive cases:

  // Postorder traversal: Left, Right, Node
  postfix_traversal(ptr->left, nth, expression); // Recurse with same nth
  postfix_traversal(ptr->right, nth, expression); // Recurse with same nth
  // Handle node case:
  // Check if node is internal node
  if (is_internal_node(ptr)) {
    // Update the cutline of the current expression_unit_t element
    expression[*nth].cutline = ptr->cutline;
  } else {
    // Update the module of the current expression_unit_t element
    expression[*nth].module= ptr->module;
  }
  // Increment the index nth
  (*nth)++;
}

// get_total_resource
// traverse through the tree and return the sum of all resource for each module
int get_total_resource(node_t* ptr) {
  // TODO:
  // Traverse in preorder. Why? Saves some extra recursive calls and looks clean.

  // Handle base case:
  if (ptr == NULL) return 0;

  // Check if current node is a leaf node, in which case we simply return its resource value
  // without bothering to call recursively (since it has no children)
  if (is_leaf_node(ptr)) return ptr->module->resource;

  // Recursive calls
  int leftSum = get_total_resource(ptr->left);
  int rightSum = get_total_resource(ptr->right);

  // Return the total sum
  return leftSum + rightSum;
}

// Procedure: init_slicing_tree
// Initialize the slicing tree by aligning modules along the horizontal line. In this procedure
// you should produce a left-skewed tree. The right child of any internal node should be a leave
// node and the subtree is recursively expanded down to the left. Take 5 modules for an example.
// The resulting tree should look like:
/*
                      root
                      /  \
                     i1  m0
                    /  \
                   i2  m1 
                  /  \
                 i3  m2
                /  \
               m4  m3
*/ 
// where the prefix i denotes an internal node (including root), and the prefix m denotes a leave
// node. Notice that each node is either an internal in which the cutline type is specified or
// a leave in which the module pointer is assigned. For an internal node, the value of its module 
// pointer should be assigned by NULL. For a leave node, the value of its cutline type should be
// specified as "UNDEFINED_CUTLINE". 
//
// In each recursive step of this function, you are passed by a parent pointer pointing to the
// parent node of which node you will generate at this step, as well as an integer index n 
// indicating the depth of the current recursion and the index of the module array to which the
// module pointer of the leave node should point to.
//

// n here is index of modules array, and therefore goes from 0,...,num_modules-1
// The function returns the parent of the new child subtree made
node_t* init_slicing_tree(node_t* par, int n) {
  
  assert(n >= 0 && n < num_modules);

  // TODO:

  // Base case: check if this is the last module to insert
  // Last module has index of num_modules-1, meaning this is the last leaf node to insert
  if (n == num_modules-1) {
    // Create a leaf node
    node_t* newLeafNodePtr = (node_t*)malloc(sizeof(node_t));
    // Assign necessary details
    newLeafNodePtr->module = modules+n; // set to point to entry in array
    newLeafNodePtr->cutline = UNDEFINED_CUTLINE;
    newLeafNodePtr->parent = par;
    newLeafNodePtr->left = NULL;
    newLeafNodePtr->right = NULL;
    // Return pointer to new node
    return newLeafNodePtr;
  }

  // Since we are not on the last node, we need to create an internal node, to be able to put
  // the current module into the right side of this internal node, and then recurse on the left side
  node_t* newInternalNodePtr = (node_t*)malloc(sizeof(node_t));
  newInternalNodePtr->module = NULL;
  newInternalNodePtr->cutline = V; // always V cutline
  newInternalNodePtr->parent = par;
  newInternalNodePtr->left = NULL;
  newInternalNodePtr->right = NULL;

  // Now, attach the current module onto the right side of the new internal node we just made
  // Create the new leaf node
  node_t* newRightLeafNodePtr = (node_t*)malloc(sizeof(node_t));
  newRightLeafNodePtr->module = modules+n; // set to point to entry in array
  newRightLeafNodePtr->cutline = UNDEFINED_CUTLINE;
  newRightLeafNodePtr->parent = newInternalNodePtr;
  newRightLeafNodePtr->left = NULL;
  newRightLeafNodePtr->right = NULL;
  // Attach new leaf node to right side of new internal node
  newInternalNodePtr->right = newRightLeafNodePtr;

  // There are still remaining nodes to insert, so recursively call, but now with
  // parent as the left child of the new internal node, and n as incremented n 
  // for the next node
  // Left child of new internal node should point to whatever this recursive call returns
  newInternalNodePtr->left = init_slicing_tree(newInternalNodePtr, n+1);

  // Now, we have made a new subtree rooted at the new internal node, so we return that
  return newInternalNodePtr;

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PREDEFINED FUNCTIONS AND PROCEDURES.                                                          //
// PLEASE DO NOT MODIFY ANY FIELD STARTING HERE.                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////

// Function: is_overlapped
// Return 1 if any overlaps among modules, and 0 otherwise.
int is_overlapped() {
  int i, j;
  int llxi, llyi, urxi, uryi;
  int llxj, llyj, urxj, uryj;
  int flag = 0;
  for(i=0; i<num_modules; ++i) {
    llxi = modules[i].llx;
    llyi = modules[i].lly;
    urxi = llxi + modules[i].w;
    uryi = llyi + modules[i].h;       
    for(j=i+1; j<num_modules; ++j) {
     llxj = modules[j].llx;
     llyj = modules[j].lly;
     urxj = llxj + modules[j].w;
     uryj = llyj + modules[j].h;

     int rxu = MIN(urxi, urxj);
     int ryu = MIN(uryi, uryj);
     int rxl = MAX(llxi, llxj);
     int ryl = MAX(llyi, llyj);

     if(rxu>rxl && ryu>ryl) {
       flag = 1;
       printf("module %d and %d overlaps.\n", modules[i].idx, modules[j].idx);
     }
    }
  }
  return flag;
}

// Procedure: pnt_expression
// Print the expression to the display.
void pnt_expression(expression_unit_t *expression, int N) {

  if(!is_valid_expression(expression, N)) {
    printf("Invalid expression. Can't print. Please check your get_expression procedure.\n");   
    return;
  }

  int i;
  for(i=0; i<N; ++i) {
    if(expression[i].cutline == UNDEFINED_CUTLINE) {
      assert(expression[i].module != NULL);
      printf("%d", expression[i].module->idx);
    }
    else {
      assert(expression[i].module == NULL);
      printf("%c", expression[i].cutline == V ? 'V' : 'H');
    }
  }
  putchar('\n');
}

// Procedure: pnt_modules
// Print the coordinates of each module.
void pnt_modules() {
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("Module %d is placed at (%d, %d) with height=%d and width=%d\n",
            modules[i].idx,
            modules[i].llx, 
            modules[i].lly,
            modules[i].h, 
            modules[i].w);
  }
} 

// Procedure: write_modules
// Write the coordinates of each module into a file.
void write_modules(const char file[]) {
  FILE *ofp = fopen(file, "w");
  int i;
  for(i=0; i<num_modules; ++i) {
    printf("%d %d %d %d %d\n",
            modules[i].idx,
            modules[i].llx, 
            modules[i].lly,
            modules[i].h, 
            modules[i].w);
  }
  fclose(ofp);
} 

// Function: get_module
// Return the module pointer to the module with the given idx.
module_t* get_module(int idx) {
  int i;
  for(i=0; i<num_modules; ++i) {
    if(idx == modules[i].idx) return &modules[i];
  }
  return NULL;
}

// Function: packing
// The main procedure of packing modules. The procedure takes the expression from the
// current slicing tree and then compute the coordinate of each module.
double packing(expression_unit_t* expression, int N) {

  if(!is_valid_expression(expression, N)) {
    return FLT_MAX;
  }

  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));

  // Iterates through the expression
  int i, j;
  cluster_t cluster, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      assert(expression[i].cutline == UNDEFINED_CUTLINE);      

      // Adjust the coordinate of the module.
      expression[i].module->llx = 0;
      expression[i].module->lly = 0;

      // Create a cluster.
      cluster.beg = i;
      cluster.end = i;
      cluster.w = expression[i].module->w;
      cluster.h = expression[i].module->h;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      assert(expression[i].cutline != UNDEFINED_CUTLINE);
      assert(stack_top >= 2);

      // Extract the top two clusters.
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];
      
      // Create a new cluster.
      cluster.beg = cluster_l.beg;
      cluster.end = cluster_r.end;

      // Horizontal cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster.
      // - x coordinate doesn't change.
      if(expression[i].cutline == H) {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->lly += cluster_l.h;
        }
        cluster.w = cluster_l.w > cluster_r.w ? cluster_l.w : cluster_r.w;
        cluster.h = cluster_l.h + cluster_r.h;
      }
      // Vertical cutline.
      // - adjust the cluster's width and height.
      // - adjust the coordinates of modules from the right cluster. 
      // - y coordinate doesn't change.
      else {
        for(j=cluster_r.beg; j<=cluster_r.end; ++j) {
          if(expression[j].module == NULL) continue;
          expression[j].module->llx += cluster_l.w;
        }
        cluster.w = cluster_l.w + cluster_r.w;
        cluster.h = cluster_l.h > cluster_r.h ? cluster_l.h : cluster_r.h;
      }

      // Insert the cluster into the stack.
      stack[stack_top++] = cluster;
    }
  }

  assert(stack_top == 1);

  double area = (double)stack[stack_top - 1].w * (double)stack[stack_top - 1].h;
  
  free(stack);

  return area;
}

// Function: is_valid_expression
int is_valid_expression(expression_unit_t* expression, int N) {

  // Initialize the stack by setting the variable stack_top as zero. The variable stack_top
  // is also denoting the size of the stack.
  int stack_top = 0;
  cluster_t* stack = (cluster_t*)malloc(N*sizeof(cluster_t));

  // Iterates through the expression
  int i;
  cluster_t cluster = {0, 0, 0, 0}, cluster_l, cluster_r;
  for(i=0; i<N; ++i) {
    // Module
    if(expression[i].module != NULL) {
      if(expression[i].cutline != UNDEFINED_CUTLINE) return 0;
      stack[stack_top++] = cluster;
    }
    // Cutline
    else {
      if(expression[i].cutline == UNDEFINED_CUTLINE) return 0;
      if(stack_top < 2) return 0;
      cluster_r = stack[--stack_top];
      cluster_l = stack[--stack_top];
      stack[stack_top++] = cluster;
    }
  }
  free(stack);
  return stack_top == 1;
}

// Procedure: read_modules
// Read the modules from a given input file and initialize all required data structure.
void read_modules(const char file[]) {
 
  int i;
  FILE* ifp = fopen(file, "r");

  assert(ifp != NULL);
  
  // Read the number of modules.
  assert(fscanf(ifp, "%d", &num_modules) == 1);
  assert(num_modules >= 2);
  
  // Allocate the memory.
  modules = (module_t*)malloc(num_modules*sizeof(module_t));

  // Read the modules one by one.
  for(i=0; i<num_modules; ++i) {
    assert(fscanf(ifp, "%d %d %d %d", &modules[i].idx, &modules[i].w, &modules[i].h, &modules[i].resource) == 4); 
    modules[i].llx = 0;
    modules[i].lly = 0;
  }

  fclose(ifp);
}

// Procedure: copy_expression
void copy_expression(expression_unit_t* lhs, expression_unit_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(expression_unit_t));
}

// Procedure: copy_modules
void copy_modules(module_t* lhs, module_t* rhs, int N) {
  memcpy(lhs, rhs, N*sizeof(module_t));
}

// Function: accept_proposal
// Accept the proposed solution.
int accept_proposal(double current, double proposal, double temperature) {
  if(proposal < current) return 1;
  if(temperature <= FROZEN) return 0;
  double prob = exp(-(double)(proposal - current) / temperature);
  return rand()/(double)RAND_MAX < prob;
}

// Function: get_rand_internal
node_t* get_rand_internal(node_t** internals, int num_internals) {
  return internals[rand()%num_internals]; 
}

// Function: get_rand_leave
node_t* get_rand_leave(node_t** leaves, int num_leaves) {
  return leaves[rand()%num_leaves]; 
}

// Function: get_random_node
node_t* get_rand_node(node_t** internals, int num_internals, node_t** leaves, int num_leaves) {
  if(rand()%2) {
    return get_rand_leave(leaves, num_leaves);
  }
  return get_rand_internal(internals, num_internals);
}

// Function: optimize
// Optimize the area of the floorplanner.
double optimize(node_t *root, int num_nodes) {
  
  // Storage for leave and internal nodes.
  int head = 0;
  int tail = 0;
  int num_leaves = 0;
  int num_internals = 0;
  node_t** queue = (node_t**)malloc(num_nodes*sizeof(node_t*));
  node_t** leaves = (node_t**)malloc(num_modules*sizeof(node_t*));
  node_t** internals = (node_t**)malloc((num_modules-1)*sizeof(node_t*));
  node_t* u;
  queue[tail++] = root;

  while(tail - head) {
    u = queue[head++];
    
    if(u->module) {
      assert(u->cutline == UNDEFINED_CUTLINE);
      leaves[num_leaves++] = u;
    }
    else {
      assert(u->cutline != UNDEFINED_CUTLINE);
      internals[num_internals++] = u;
    }

    if(u->left) queue[tail++] = u->left;
    if(u->right) queue[tail++] = u->right;
  }

  assert(num_leaves == num_modules);
  assert(num_internals == num_modules - 1);

  // Simulated annealing.
  srand(time(0));
  expression_unit_t* best_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  expression_unit_t* curr_expression = (expression_unit_t*)malloc(num_nodes*sizeof(expression_unit_t));
  module_t* best_modules = (module_t*)malloc(num_modules*sizeof(module_t));
  
  int i, key;
  double best_area, curr_area;
  double temperature = 100.0;
  node_t* a;
  node_t* b;

  // Initialization.
  get_expression(root, num_nodes, best_expression);
  best_area = packing(best_expression, num_nodes);
  memcpy(best_modules, modules, num_modules*sizeof(module_t));

  while(temperature > FROZEN) {
    
    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {

      key = rand()%4;
      
      switch(key) {

        // Perform recut.
        case 0:
          recut(get_rand_internal(internals, num_internals));
        break;
        
        // Perform rotate.
        case 1:
          rotate(get_rand_leave(leaves, num_leaves));
        break;
        
        // Perform swap_module.
        case 2:
          do {
            a = get_rand_leave(leaves, num_leaves);
            b = get_rand_leave(leaves, num_leaves);
          } while(a == b);
          swap_module(a, b);
        break;
        
        // Perform swap_topology.
        default:
          do {        
            a = get_rand_node(internals, num_internals, leaves, num_leaves);
            b = get_rand_node(internals, num_internals, leaves, num_leaves);
          } while(is_in_subtree(a, b) || is_in_subtree(b, a));
          swap_topology(a, b);
        break;
      }

      // Evaluate the area.
      get_expression(root, num_nodes, curr_expression);
      curr_area = packing(curr_expression, num_nodes);
      if(curr_area < best_area) {
        best_area = curr_area;
        copy_expression(best_expression, curr_expression, num_nodes);
        memcpy(best_modules, modules, num_modules*sizeof(module_t));
        //copy_modules(best_modules, modules, num_modules);
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }

  memcpy(modules, best_modules, num_modules*sizeof(module_t));
  best_area = packing(best_expression, num_nodes);
 
  /*// Secondary optimization.
  temperature = 100.0;
  while(temperature > FROZEN) {
    
    // Start at a step.
    copy_expression(curr_expression, best_expression, num_nodes);
    copy_modules(modules, best_modules, num_modules);
    
    // Generate the neighboring solution.
    for(i=0; i<MAX_NUM_RAND_STEPS; ++i) {

      copy_expression(next_expression, curr_expression, num_nodes);

      key = rand()%4;
      
      switch(key) {

        // Perform recut.
        case 0:
          do{
            j = rand() % num_nodes;
          } while(next_expression[j].cutline == UNDEFINED_CUTLINE);
          next_expression[j].cutline = next_expression[j].cutline == V ? H : V;
        break;
        
        // Perform rotate.
        case 1:
          do{
            j = rand() % num_nodes;
          } while(next_expression[j].module == NULL);
          next_expression[j].module->w = next_expression[j].module->w ^ next_expression[j].module->h;
          next_expression[j].module->h = next_expression[j].module->w ^ next_expression[j].module->h;
          next_expression[j].module->w = next_expression[j].module->w ^ next_expression[j].module->h;
          
        break;
        
        // Perform swap_module.
        case 2:
          do {
            j = rand() % num_nodes;
            k = rand() % num_nodes;
          } while(j == k || next_expression[j].module == NULL || next_expression[k].module == NULL);
          tmp = next_expression[k].module;
          next_expression[k].module = next_expression[j].module;
          next_expression[j].module = tmp;
        break;
        
        // Perform swap_topology.
        default:
          do {
            do{
              j = rand() % num_nodes;
              k = rand() % num_nodes;
            } while(j == k);
            e = next_expression[k];
            next_expression[k] = next_expression[j];
            next_expression[j] = e;
          } while (!is_valid_expression(next_expression, num_nodes));
        break;
      }

      // Evaluate the area.
      curr_area = packing(curr_expression, num_nodes);
      next_area = packing(next_expression, num_nodes);
      if(accept_proposal(curr_area, next_area, temperature)){
        if(next_area < best_area) {
          best_area = next_area;
          copy_expression(best_expression, next_expression, num_nodes);
        }
        copy_expression(curr_expression, next_expression, num_nodes);
        curr_area = next_area;
      }
    }
    temperature *= TEMPERATURE_DECREASING_RATE;
  }

  best_area = packing(best_expression, num_nodes);*/

  
  free(queue);
  free(leaves);
  free(internals);
  free(best_expression);
  free(curr_expression);
  free(best_modules);

  return best_area;
}


