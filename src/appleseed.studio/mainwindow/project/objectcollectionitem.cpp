
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "objectcollectionitem.h"

// appleseed.studio headers.
#include "mainwindow/project/entityitem.h"
#include "mainwindow/project/projectbuilder.h"

// appleseed.renderer headers.
#include "renderer/api/geometry.h"

// Qt headers.
#include <QFileDialog>
#include <QMenu>
#include <QString>
#include <QStringList>

using namespace renderer;

namespace appleseed {
namespace studio {

ObjectCollectionItem::ObjectCollectionItem(
    Assembly&           assembly,
    ObjectContainer&    objects,
    ProjectBuilder&     project_builder)
  : CollectionItem("Objects", objects)
  , m_assembly(assembly)
  , m_project_builder(project_builder)
{
}

QMenu* ObjectCollectionItem::get_context_menu() const
{
    QMenu* menu = new QMenu(treeWidget());
    menu->addAction("Import Objects...", this, SLOT(slot_import_objects()));
    return menu;
}

void ObjectCollectionItem::slot_import_objects()
{
    QFileDialog::Options options;
    QString selected_filter;

    const QStringList filepaths =
        QFileDialog::getOpenFileNames(
            treeWidget(),
            "Import Objects...",
            "",
            "Geometry Files (*.obj);;All Files (*.*)",
            &selected_filter,
            options);

    for (int i = 0; i < filepaths.size(); ++i)
    {
        m_project_builder.insert_objects(
            m_assembly,
            filepaths[i].toStdString());
    }

/*
    if (!filepaths.empty())
        emit project_modified();
*/
}

}   // namespace studio
}   // namespace appleseed
