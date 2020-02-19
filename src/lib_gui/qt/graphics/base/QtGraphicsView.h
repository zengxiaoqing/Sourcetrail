#ifndef QT_GRAPHICS_VIEW_H
#define QT_GRAPHICS_VIEW_H

#include <memory>

#include <QGraphicsView>

#include "types.h"

class QPushButton;
class QTimer;
class QtGraphEdge;
class QtGraphNode;
class QtSelfRefreshIconButton;

class QtGraphicsView: public QGraphicsView
{
	Q_OBJECT

public:
	QtGraphicsView(QWidget* parent);

	float getZoomFactor() const;
	void setAppZoomFactor(float appZoomFactor);

	void setSceneRect(const QRectF& rect);

	QtGraphNode* getNodeAtCursorPosition() const;
	QtGraphEdge* getEdgeAtCursorPosition() const;

	void ensureVisibleAnimated(const QRectF& rect, int xmargin = 50, int ymargin = 50);

	void updateZoom(float delta);

protected:
	void resizeEvent(QResizeEvent* event);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

	void wheelEvent(QWheelEvent* event);

	void contextMenuEvent(QContextMenuEvent* event);

signals:
	void emptySpaceClicked();
	void characterKeyPressed(QChar c);
	void resized();

private slots:
	void updateTimer();
	void stopTimer();

	void openInTab();

	void exportGraph();
	void copyNodeName();

	void collapseNode();
	void expandNode();

	void showInIDE();
	void showDefinition();
	void hideNode();
	void hideEdge();
	void bookmarkNode();

	void zoomInPressed();
	void zoomOutPressed();

	void hideZoomLabel();

	void legendClicked();

private:
	bool moves() const;

	void setZoomFactor(float zoomFactor);
	void updateTransform();

	QPoint m_last;

	float m_zoomFactor;
	float m_appZoomFactor;

	bool m_up;
	bool m_down;
	bool m_left;
	bool m_right;
	bool m_shift;

	std::wstring m_clipboardNodeName;
	Id m_openInTabNodeId;
	Id m_hideNodeId;
	Id m_hideEdgeId;
	Id m_bookmarkNodeId;
	Id m_collapseNodeId;
	Id m_expandNodeId;

	std::shared_ptr<QTimer> m_timer;
	std::shared_ptr<QTimer> m_timerStopper;
	std::shared_ptr<QTimer> m_zoomLabelTimer;

	QAction* m_openInTabAction;

	QAction* m_copyNodeNameAction;
	QAction* m_collapseAction;
	QAction* m_expandAction;
	QAction* m_showInIDEAction;
	QAction* m_showDefinitionAction;
	QAction* m_hideNodeAction;
	QAction* m_hideEdgeAction;
	QAction* m_bookmarkNodeAction;

	QAction* m_exportGraphAction;

	QPushButton* m_zoomState;
	QtSelfRefreshIconButton* m_zoomInButton;
	QtSelfRefreshIconButton* m_zoomOutButton;

	QtSelfRefreshIconButton* m_legendButton;

	float m_zoomInButtonSpeed;
	float m_zoomOutButtonSpeed;
};

#endif	  // QT_GRAPHICS_VIEW_H