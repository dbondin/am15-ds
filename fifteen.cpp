#include <iostream>

#include <cstring>
#include <cstdarg>
#include <cmath>
#include <list>

#define FIELD_WIDTH 3
#define FIELD_HEIGHT 3

enum MOVE_DIRECTION {
	_START = 0, LEFT = 0, RIGHT, UP, DOWN, _END
};

class Field {
private:
	unsigned char elem[FIELD_HEIGHT * FIELD_WIDTH];
	unsigned char zero_pos;
public:
	Field();
	Field(int e, ...);
	bool move(MOVE_DIRECTION md);
	bool equals(const Field & other) const;
	long get_check_index() const;
	void print() const;
};

void
Field::print() const {
	for(int i=0; i<FIELD_HEIGHT; ++i) {
		for(int j=0; j<FIELD_WIDTH; ++j) {
			char e = elem[i * FIELD_WIDTH + j];
			if(e == 0) {
				e = '_';
			}
			else {
				e += '0';
			}
			std::cout<<e<<" ";
		}
		std::cout<<std::endl;
	}
}

long
Field::get_check_index() const {
	long result = 0;

	for(int i=0; i<FIELD_HEIGHT * FIELD_WIDTH; ++i) {
		result *= (FIELD_HEIGHT * FIELD_WIDTH);
		result += elem[i];
	}

	return result;
}

Field::Field() {
	zero_pos = 0;
}

bool Field::equals(const Field & other) const {
	return (memcmp(this->elem, other.elem, FIELD_WIDTH * FIELD_HEIGHT) == 0);
}

bool Field::move(MOVE_DIRECTION md) {
	unsigned char new_zero_pos;
	switch (md) {
	case LEFT:
		if((zero_pos % FIELD_WIDTH) == 0) {
			return false;
		}
		new_zero_pos = zero_pos - 1;
		break;
	case RIGHT:
		if((zero_pos % FIELD_WIDTH) == (FIELD_WIDTH - 1)) {
			return false;
		}
		new_zero_pos = zero_pos + 1;
		break;
	case UP:
		if(zero_pos < FIELD_WIDTH) {
			return false;
		}
		new_zero_pos = zero_pos - FIELD_WIDTH;
		break;
	case DOWN:
		if(zero_pos >= (FIELD_WIDTH * (FIELD_HEIGHT - 1))) {
			return false;
		}
		new_zero_pos = zero_pos + FIELD_WIDTH;
		break;
	default:
		return false;
	}

	unsigned char tmp = elem[zero_pos];
	elem[zero_pos] = elem[new_zero_pos];
	elem[new_zero_pos] = tmp;

	zero_pos = new_zero_pos;

	return true;
}


Field::Field(int e, ...) {
	va_list argp;
	va_start(argp, e);

	//TODO: Add check to ensure all values are valid

	elem[0] = e;

	for(int i=1; i<FIELD_WIDTH * FIELD_HEIGHT; ++i) {
		unsigned char el = (unsigned char) va_arg(argp, int);
		elem[i] = el;
	}

	zero_pos = 0;
	for(int i=0; i<FIELD_WIDTH * FIELD_HEIGHT; ++i) {
		if(elem[i] == 0) {
			zero_pos = i;
			break;
		}
	}

	va_end(argp);
}

const Field WIN1(1, 2, 3, 4, 5, 6, 7, 8, 0);
const Field WIN2(1, 2, 3, 5, 4, 6, 8, 7, 0);

bool check_if_win(const Field & f) {
	return f.equals(WIN1) || f.equals(WIN2);
}

class TreeNode {
private:
	Field field;
	const TreeNode * parent;
public:
	TreeNode();
	TreeNode(const Field & f, const TreeNode * parent);
	Field get_field() const;
	const TreeNode * get_parent() const;
};

Field
TreeNode::get_field() const {
	return this->field;
}

const TreeNode *
TreeNode::get_parent() const {
	return this->parent;
}

TreeNode::TreeNode() : field(), parent(NULL) {
}


TreeNode::TreeNode(const Field & f, const TreeNode * parent) {
	this->field = f;
	this->parent = parent;
}

const Field START(1, 2, 5, 4, 3, 0, 7, 6, 8);

unsigned long factorial(unsigned long i) {
	if(i<2) {
		return 1;
	}
	return i * factorial(i-1);
}

TreeNode * NODES;

int CURRENT_NODE = 0;
int NODES_COUNT = 0;

bool * CHECK;

void process_win(int node_index) {
	const TreeNode * n = &(NODES[node_index]);
	std::list<Field> lst;
	while(true) {
		lst.push_front(n->get_field());
		n = n->get_parent();
		if(n == NULL) {
			break;
		}
	}
	int num=0;
	for(std::list<Field>::iterator i=lst.begin(); i!=lst.end(); ++i) {
		std::cout<<"-------------- "<<++num<<std::endl;
		i->print();
	}
	std::cout<<"END"<<std::endl;
}

int main(int argc, char **argv) {

	CHECK = new bool[(unsigned long)pow((FIELD_HEIGHT * FIELD_WIDTH), (FIELD_HEIGHT * FIELD_WIDTH))];
	memset(CHECK, 0, (unsigned long)pow((FIELD_HEIGHT * FIELD_WIDTH), (FIELD_HEIGHT * FIELD_WIDTH)));

	NODES = new TreeNode[factorial(FIELD_WIDTH * FIELD_HEIGHT) / 2];

	if(check_if_win(START)) {
		std::cout<<"Сразу WIN"<<std::endl;
	}

	NODES[NODES_COUNT] = TreeNode(START, NULL);
	NODES_COUNT++;

	bool found = false;

	while(!found) {

		if(CURRENT_NODE >= NODES_COUNT) {
			break;
		}

		for(long dir = _START; dir < _END; ++dir) {
			Field f = NODES[CURRENT_NODE].get_field();
			bool status = f.move((MOVE_DIRECTION)dir);
			if(status) {
				// Already was in place?
				long check_index = f.get_check_index();
				if(CHECK[check_index] == false) {
					CHECK[check_index] = true;
					TreeNode new_node(f, &(NODES[CURRENT_NODE]));
					NODES[NODES_COUNT] = new_node;

					//std::cout<<"ADD NEW ONE"<<std::endl;
					//f.print();

					if(check_if_win(f)) {
						found = true;
						process_win(NODES_COUNT);
						break;
					}
					NODES_COUNT++;
				}
			}
		}
		CURRENT_NODE ++;
	}

	delete [] NODES;
	delete [] CHECK;

	return 0;
}

