/**
 * AST Parser
 * - no operator precedence
 * - parenthesis
 * - 1 char = 1 token
 */
namespace parser {
  struct node {
    node *l,*r; int val; bool op;
    node(bool o=true) : l(0), r(0), val(0), op(o) {}
    virtual int eval() = 0;
  };
  struct val_node : node {
    val_node(int v=0) : node(0) {
      val = v;
    }
    int eval() {
      // TODO: Return value of node
    }
  };
  struct add_node : node {
    int eval() {
      return l->eval() + r->eval();
    }
  };
  struct sub_node : node {
    int eval() {
      return l->eval() - r->eval();
    }
  };
  struct mul_node : node {
    int eval() {
      return l->eval() * r->eval();
    }
  };
  node* get_op(char c) {
    switch (c) {
      case '+': return new add_node();
      case '-': return new sub_node();
      case '*': return new mul_node();
    }
    return 0;
  }
  node* parse(const string& exp) {
    stack<node*> op;
    queue<node*> out;
    node* cur;
    for (char c : exp) {
      if (c == '(') {
        op.push(0);
      } else if (c == ')') {
        for (; op.top(); op.pop()) {
          out.push(op.top());
        } op.pop();
      } else {
        cur = get_op(c);
        if (cur) {
          op.push(cur);
        } else {
          cur = new val_node();
          // TODO: Assign value to node
          cur->val = -1
          out.push(cur);
        }
      }
    }
    for (; op.size(); op.pop()) {
      out.push(op.top());
    }
    for (; out.size(); out.pop()) {
      cur = out.front();
      if (cur->op) {
        cur->r = op.top(); op.pop();
        cur->l = op.top(); op.pop();
        cur->op = 0;
      }
      op.push(cur);
    }
    assert(op.size() == 1);
    return op.top();
  }
}

