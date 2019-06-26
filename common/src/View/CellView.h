/*
 Copyright (C) 2010-2017 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TrenchBroom_CellView_h
#define TrenchBroom_CellView_h

#include "Renderer/RenderUtils.h"
#include "Renderer/Transformation.h"
#include "Renderer/FontDescriptor.h"
#include "Preferences.h"
#include "View/CellLayout.h"
#include "View/RenderView.h"

#include <QPoint>

class QScrollBar;
class QDrag;
class QMimeData;

namespace TrenchBroom {
    namespace View {
        class GLContextManager;

        class CellView : public RenderView {
            Q_OBJECT
        protected:
            using Layout = CellLayout;
            using Group = LayoutGroup;
            using Row = LayoutRow;
            using Cell = LayoutCell;
        private:
            Layout m_layout;
            Cell* m_selectedCell;
            bool m_layoutInitialized;

            bool m_valid;

            QScrollBar* m_scrollBar;
            QPoint m_lastMousePos;
            bool m_potentialDrag;

            void updateScrollBar();
            void initLayout();
            void reloadLayout();
            void validate();
        public:
            CellView(GLContextManager& contextManager, QScrollBar* scrollBar = nullptr);
            void invalidate();
            void clear();
            void resizeEvent(QResizeEvent* event) override;
        private:
            void onScrollBarValueChanged();
            void onScrollBarActionTriggered(int action);
        public:
            void mousePressEvent(QMouseEvent* event) override;
            void mouseReleaseEvent(QMouseEvent* event) override;
            void mouseMoveEvent(QMouseEvent* event) override;
            void wheelEvent(QWheelEvent* event) override;

            void startDrag(const QMouseEvent* event);
            void scroll(const QMouseEvent* event);
            void updateTooltip(const QMouseEvent* event);
        private:
            void doRender() override;
            void setupGL();

            virtual void doInitLayout(Layout& layout) = 0;
            virtual void doReloadLayout(Layout& layout) = 0;
            virtual void doClear();
            virtual void doRender(Layout& layout, float y, float height) = 0;
            virtual void doLeftClick(Layout& layout, float x, float y);

            virtual bool dndEnabled();
            virtual QPixmap dndImage(const Cell& cell);
            virtual QString dndData(const Cell& cell);
            virtual QString tooltip(const Cell& cell);
        public: // implement InputEventProcessor interface
            void processEvent(const KeyEvent& event) override;
            void processEvent(const MouseEvent& event) override;
            void processEvent(const CancelEvent& event) override;
        };
    }
}

#endif
