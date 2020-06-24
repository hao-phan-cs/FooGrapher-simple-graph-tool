#include "headers/GraphGraphicsView.h"
#include <QDebug>

GraphGraphicsView::GraphGraphicsView() {
    setDragMode(ScrollHandDrag);
    moving = false;
    selectTargetNode = false;
    isRunningAlgoDemo = false;
    currentScale = 1.;
}

void GraphGraphicsView::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.1;
    if (event->delta() > 0 && currentScale <= scaleMax) {
        scale(scaleFactor, scaleFactor);
        currentScale *= scaleFactor;
    } else {
        scale(1 / scaleFactor, 1 / scaleFactor);
        currentScale /= scaleFactor;
    }
}

void GraphGraphicsView::contextMenuEvent(QContextMenuEvent *event) {
    for (auto gi: scene()->selectedItems())
        gi->setSelected(false);

    QList<QGraphicsItem *> clickedItems = items(event->pos());
    if (!clickedItems.empty()) {
        auto item = clickedItems[0];
        item->setSelected(true);

        auto *arcItem = dynamic_cast<ArcGraphicsItem *>(item);
        auto *nodeItem = dynamic_cast<NodeGraphicsItem *>(item);
        if (nodeItem) {
            int id = nodeItem->getNode()->getId();
            emit selectedNode(id);
            QMenu menu;
            menu.addAction("&Delete");
            menu.addAction("&Isolate");
            menu.addAction("Re&name");
            menu.addSeparator();
            menu.addAction("&Set arc to (Select other node by mouse)");
            menu.addSeparator();
            menu.addAction("BFS from here");
            menu.addAction("DFS from here");
            menu.addAction("Find path to");
            QAction *act = menu.exec(event->globalPos());
            if (act != nullptr) {
                if (act->text() == "&Delete")
                        emit removeNode(id);
                if (act->text() == "&Isolate")
                        emit isolateNode(id);
                if (act->text() == "Re&name")
                        emit editNode(id);
                if (act->text().contains("&Set arc to")) {
                    selectTargetNode = true;
                    this->itemFrom = nodeItem;
                }
                if (act->text().contains("BFS"))
                        emit startAlgorithm("BFS", id);
                if (act->text().contains("DFS"))
                        emit startAlgorithm("DFS", id);
                if (act->text().contains("Find path"))
                        emit startAlgorithm("Find path", id);
            } else {
                item->setSelected(false);
            }
        } else if (arcItem) {
            QMenu menu;
            menu.addAction("&Delete");
            menu.addAction("Adjust &weight");
            emit selectedArc(arcItem->arc().first, arcItem->arc().second);
            QAction *act = menu.exec(event->globalPos());
            if (act != nullptr) {
                if (act->text() == "&Delete")
                        emit removeArc(arcItem->arc().first, arcItem->arc().second);
                if (act->text() == "Adjust &weight")
                        emit setArc(arcItem->arc().first, arcItem->arc().second);
            }
        }
    } else {
        if (!scene()->selectedItems().empty())
            scene()->selectedItems()[0]->setSelected(false);
        QMenu menu;
        menu.addAction("New &node");
        //menu.addAction("&Refresh");
        QAction *act = menu.exec(event->globalPos());
        if (act) {
            if (act->text() == "New &node")
                    emit addNewNode(mapToScene(event->pos()));
            //else if (act->text() == "&Refresh") {
            //    dynamic_cast<GraphGraphicsScene*>(scene())->reloadData();
            //    redraw();
            //}
        }
    }
}

void GraphGraphicsView::mousePressEvent(QMouseEvent *event) {
    for (auto si: scene()->selectedItems()) {
        auto ni = dynamic_cast<NodeGraphicsItem *>(si);
        if (ni) ni->setOnSelectedColor(NodeGraphicsItem::defaultOnSelectedColor());
        else {
            auto ai = dynamic_cast<ArcGraphicsItem *>(si);
            if (ai) ai->setOnSelectedColor(ArcGraphicsItem::defaultOnSelectedColor());
        }
    }

    auto graphScene = dynamic_cast<GraphGraphicsScene *>(scene());
    if (graphScene->unique_timer) {
        graphScene->unique_timer->stop();
    }
    graphScene->resetAfterDemoAlgo();

    if (!selectTargetNode)
        QGraphicsView::mousePressEvent(event);
    if (selectTargetNode) {
        QList<QGraphicsItem *> itemsTo = items(event->pos());
        if (!itemsTo.empty()) {
            auto *castedItemTo = dynamic_cast<NodeGraphicsItem *>(itemsTo[0]);
            if (itemFrom && castedItemTo && itemFrom != castedItemTo) {
                castedItemTo->setSelected(false);
                emit setArc(itemFrom->getNode()->getId(), castedItemTo->getNode()->getId());
            }
        }
    }
    selectTargetNode = false;
    this->itemFrom = nullptr;
    scene()->update();
    viewport()->update();
}

void GraphGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (!scene()->selectedItems().empty()) {
        auto fni = dynamic_cast<NodeGraphicsItem *>(scene()->selectedItems()[0]);
        auto fai = dynamic_cast<ArcGraphicsItem *>(scene()->selectedItems()[0]);
        if (fai) emit selectedArc(fai->arc().first, fai->arc().second);
        else if (fni) emit selectedNode(fni->getNode()->getId());
    }
    if (items(event->pos()).empty())
            emit unSelect();
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphGraphicsView::setScene(GraphGraphicsScene *scene) {
    connect(scene, SIGNAL(graphChanged()), this, SLOT(redraw()));
    connect(scene, SIGNAL(needRedraw()), this, SLOT(redraw()));
    QGraphicsView::setScene(scene);
}

void GraphGraphicsView::redraw() {
    this->viewport()->update();
}


