<?xml version="1.0" encoding="utf-8"?>
<!-- Created by Leo (http://leoeditor.com/leo_toc.html) -->
<?xml-stylesheet ekr_test?>
<leo_file xmlns:leo="http://www.leo-editor.org/2011/leo" >
<leo_header file_format="2" tnodes="0" max_tnode_index="0" clone_windows="0"/>
<globals body_outline_ratio="0.5" body_secondary_ratio="0.5">
	<global_window_position top="50" left="50" height="500" width="700"/>
	<global_log_window_position top="0" left="0" height="0" width="0"/>
</globals>
<preferences/>
<find_panel_settings/>
<vnodes>
<v t="peckj.20140128081459.13239"><vh>design-notes accumulator.py</vh>
<v t="peckj.20140128081459.13240" a="E"><vh>class Accumulator</vh>
<v t="peckj.20140128081459.13241"><vh>method __init__</vh></v>
<v t="peckj.20140128081459.13242"><vh>property value</vh></v>
<v t="peckj.20140128081459.13243"><vh>method tick</vh></v>
</v>
<v t="peckj.20140128081459.13244"><vh>class ReverseAccumulator</vh>
<v t="peckj.20140128081459.13241"></v>
<v t="peckj.20140128081459.13242"></v>
<v t="peckj.20140128081459.13247"><vh>method tick</vh></v>
</v>
</v>
<v t="peckj.20140128081459.13248"><vh>@button design-to-file</vh>
<v t="peckj.20140128081459.13317"><vh>&lt;&lt; declarations &gt;&gt;</vh></v>
<v t="peckj.20140128081459.13251"><vh>create_file_node</vh></v>
<v t="peckj.20140128081459.13252" a="E"><vh>create_class_nodes</vh>
<v t="peckj.20140128081459.13314" a="E"><vh>create_class_node</vh>
<v t="peckj.20140128081459.13315" a="E"><vh>create_method_nodes</vh>
<v t="peckj.20140128081459.13316"><vh>create_method_node</vh></v>
</v>
</v>
</v>
</v>
</vnodes>
<tnodes>
<t tx="peckj.20140128081459.13239">A general accumulator and reverse accumulator class library</t>
<t tx="peckj.20140128081459.13240">An accumulator that counts up</t>
<t tx="peckj.20140128081459.13241">constructor</t>
<t tx="peckj.20140128081459.13242">the current count</t>
<t tx="peckj.20140128081459.13243">increases value by 1</t>
<t tx="peckj.20140128081459.13244">An accumulator that counts down</t>
<t tx="peckj.20140128081459.13247">decreases value by 1</t>
<t tx="peckj.20140128081459.13248">@language python

&lt;&lt; declarations &gt;&gt;
@others

# get the design node
designnode = p.copy()
if not designnode.h.startswith('design-notes'):
  g.es('Not a design-notes node, exiting.', color='red')
else:
  # create the @file node
  filenode = create_file_node(designnode)
  
  # create the class nodes
  create_class_nodes(designnode, filenode)
  
  c.redraw_now()
  g.es('Done', color='forestgreen')
  


</t>
<t tx="peckj.20140128081459.13251">def create_file_node(designnode):
  # create the @file node
  filename = designnode.h.split(' ',1)[1] # trim the 'design-notes' from the headline
  filenode = designnode.insertAfter() # create a new child
  filenode.h = '@file %s' % filename # set the headline of the new node
  # set the body
  filenode.b = """@language python
  
%s
%s
%s

%s
""" % (docstring, imports, declarations, others)
  
  # create the docstring node
  docstringnode = filenode.insertAsLastChild()
  docstringnode.h = docstring
  docstringnode.b = "\"\"\"%s\"\"\"" % designnode.b
  
  # create the imports node (empty)
  importsnode = docstringnode.insertAfter()
  importsnode.h = imports
  
  # create the declarations node (empty)
  declarationsnode = importsnode.insertAfter()
  declarationsnode.h = declarations
  
  # return the filenode
  return filenode</t>
<t tx="peckj.20140128081459.13252">def create_class_nodes(designnode, filenode):
  for ch in designnode.children():
    create_class_node(filenode, ch)
</t>
<t tx="peckj.20140128081459.13314">def create_class_node(filenode, classnode):
  # create the class node
  newclassnode = filenode.insertAsLastChild()
  newclassnode.h = classnode.h
  newclassnode.b = """%s:
  %s
  %s
""" % (classnode.h, docstring, others)
  # create the docstring node
  docstringnode = newclassnode.insertAsLastChild()
  docstringnode.h = docstring
  docstringnode.b = "\"\"\"%s\"\"\"" % classnode.b
  
  # create the method nodes
  # ignore the property nodes -- they're notes
  create_method_nodes(newclassnode, classnode)</t>
<t tx="peckj.20140128081459.13315">def create_method_nodes(classnode, designnode):
  for ch in designnode.children():
    if ch.h.startswith('method'):
      create_method_node(classnode, ch)
</t>
<t tx="peckj.20140128081459.13316">def create_method_node(classnode, methodnode):
  newmethodnode = classnode.insertAsLastChild()
  newmethodnode.h = methodnode.h.split(' ',1)[1]
  newmethodnode.b = """def %s(self):
    \"\"\"%s\"\"\"
    pass
""" % (newmethodnode.h, methodnode.b)</t>
<t tx="peckj.20140128081459.13317"># the following are Leo directives, so we have to trick leo by constructing them in the script
others = '@' + 'others'
docstring = '&lt;' + '&lt;' + ' docstring ' + '&gt;' + '&gt;'
imports = '&lt;' + '&lt;' + ' imports ' + '&gt;' + '&gt;'
declarations = '&lt;' + '&lt;' + ' declarations ' + '&gt;' + '&gt;'</t>
</tnodes>
</leo_file>
