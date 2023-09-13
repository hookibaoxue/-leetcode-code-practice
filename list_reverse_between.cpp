#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

void printList(ListNode* head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

/***********************************方法1 start*********************************/ 
ListNode* reverseBetween_1(ListNode* head, int m, int n) {
    if (!head || m == n) {
        return head;
    }
    
	// 建一个头节点,便于统一处理
	ListNode* res = new ListNode(-1);
	res->next = head;

	// 找到需要反转节点的前一个节点
	ListNode* pre = res;
	for (int i = 0; i < m - 1; ++i)
	{
		pre = pre->next;
	}

	// 找到需要反转节点中最后一个节点
	ListNode* right_node = pre;
	for (int i = 0; i < n - m + 1; ++i)
	{
		right_node = right_node->next;
	}
	
	//指向需要反转的第一个节点
	ListNode* left_node = pre->next;

	//指向反转节点中最后一个节点的后续节点
	ListNode* cur = right_node->next;

	//将链表关联移除(区间范围内的链表成为子链表)
	pre->next = nullptr;
	right_node->next = nullptr;

	// 反转子链表
	ListNode* temp_pre = nullptr;
	ListNode* temp_cur = left_node;
	while (temp_cur != nullptr)
	{
		ListNode * temp_next = temp_cur->next;
		temp_cur->next = temp_pre;
		temp_pre = temp_cur;
		temp_cur = temp_next;
	}

	//将链表链接起来
	pre->next = temp_pre;
	left_node->next = cur;

	return res->next;
}
/***********************************方法1 end*********************************/ 

/*****************************方法2 start***************************************/
ListNode* reverseBetween_2(ListNode* head, int m, int n) {
	ListNode* res = new ListNode(-1);
	res->next = head;

	ListNode* pre = res;
	for (int i = 0; i < m - 1; ++i)
	{
		pre = pre->next;
	}

	ListNode* cur = pre->next;

	for (int i = m; i < n; ++i)
	{
		ListNode* temp_node = cur->next;
		cur->next = temp_node->next;
		temp_node->next = pre->next;
		pre->next = temp_node;
	}
	
	return res->next;
}
/*****************************方法2 end****************************************/
int main() {
	ListNode* head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);

	cout << "Original List: ";
	printList(head);

	int m = 2, n = 4;
	head = reverseBetween_1(head, m, n);
	cout << "Modified List1: ";
	printList(head);

	head = reverseBetween_2(head, m, n);
	cout << "Modified List2: ";
	printList(head);
	return 0;
}
