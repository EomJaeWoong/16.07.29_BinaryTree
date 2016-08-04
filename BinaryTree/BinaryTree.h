#ifndef __BINARYTREE__H__
#define __BINARYTREE__H__

#define LEFT			1
#define RIGHT			2

struct st_TNODE
{
	struct st_TNODE *pLeft;
	struct st_TNODE *pRight;

	int iData;
};


class BSearchTree
{
public:

	BSearchTree();
	~BSearchTree();

	//------------------------------------------------------
	// 새로운 데이터를 추가한다.
	//------------------------------------------------------
	bool		InsertNode(int iData);

	//------------------------------------------------------
	// 트리의 데이터를 삭제한다.
	//------------------------------------------------------
	void		deleteNode(int iData);

	//------------------------------------------------------
	// 트리 전체 삭제
	//------------------------------------------------------
	bool		ReleaseTree(void);

	//------------------------------------------------------
	// 전위순회 방식 출력
	//------------------------------------------------------
	void		PreorderPrint(st_TNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	//------------------------------------------------------
	// 중위순회 방식 출력
	//------------------------------------------------------
	void		InorderPrint(st_TNODE *pNode = NULL, int iDepth = 0, int iLR = 0);

	//------------------------------------------------------
	// 후위순회 방식 출력
	//------------------------------------------------------
	void		PostorderPrint(st_TNODE *pNode = NULL, int iDepth = 0, int iLR = 0);


	st_TNODE *GetRoot();
private:

	//------------------------------------------------------
	// InsertNode 내부에서 호출되는 위치 찾아 추가 재귀 함수
	//------------------------------------------------------
	bool		linkNode(st_TNODE *pParent, st_TNODE *pChild);

	//------------------------------------------------------
	// deleteNode 내부에서 호출되는 위치 찾아 삭제 재귀 함수
	//------------------------------------------------------
	bool		unlinkNode(st_TNODE *pNODE, st_TNODE *pParent, int iData);

	//------------------------------------------------------
	// releaseNode 내부에서 호출되는 노드삭제용 재귀함수
	//------------------------------------------------------
	void		releaseNode(st_TNODE *pNode);

	//------------------------------------------------------
	// 노드 생성
	//------------------------------------------------------
	void		CreateNode(st_TNODE *pNode, int iData);

	st_TNODE	*m_pRoot;
	int		m_iNodeCount;

};


#endif