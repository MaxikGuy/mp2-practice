#ifndef _TSTACK_H
#define _TSTACK_H

template <typename T>
class TStack {
private:
	int maxSize;
	int top;
	T* elems;
public:
	TStack(int _maxSize = 50);
	TStack(const TStack<T>& s, int extraSize = 0);
	virtual ~TStack();

	bool IsEmpty(void) const noexcept;
	bool IsFull(void) const noexcept;

	T Top();

	void Push(const T& e);
	void Pop();

	void DUBUG_Print();
};

template <typename T>
TStack<T>::TStack(int _maxSize) {
	if (_maxSize <= 0) throw "Error: maxSize must be bigger than 0.";
	maxSize = _maxSize;
	top = -1;
	elems = new T[maxSize];
}
template <typename T>
TStack<T>::TStack(const TStack<T>& s, int extraSize) {
	if (extraSize < 0) throw "Error: Stack extra size less than 0.";

	maxSize = s.maxSize + extraSize;
	top = s.top;
	elems = new T[maxSize];

	for (int i = 0; i <= top; i++)
		elems[i] = s.elems[i];
}
template <typename T>
TStack<T>::~TStack() {
	delete[] elems;
}

template <typename T>
bool TStack<T>::IsEmpty(void) const noexcept {
	return (top == -1);
}
template <typename T>
bool TStack<T>::IsFull(void) const noexcept {
	return (top == maxSize - 1);
}

template <typename T>
T TStack<T>::Top() {
	if (IsEmpty()) throw "Error: stack is empty.";
	return elems[top];
}

template <typename T>
void TStack<T>::Push(const T& e) {
	if (IsFull()) throw "Error: stack is full.";
	elems[++top] = e;
}
template <typename T>
void TStack<T>::Pop() {
	if (IsEmpty()) throw "Error: stack is empty.";
	top--;
}

template <typename T>
void TStack<T>::DUBUG_Print() {
	for (int i = 0; i < top; i++)
		cout << elems[i] << ' ';
}

#endif // !_TSTACK_H
