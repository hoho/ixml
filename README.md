IndentXML
=========

**IndentXML** doesn't describe some new markup language. This format is just another way to represent **XML documents**. IndentXML is desined to cover everyday needs and should handle these needs like gracefully. This means that some rare use cases of XML are still under consideration. So, most of XML documents could be converted to IndentXML and back automatically.


Basic principles
----------------

* Parent-child relation is settled with indentation (like code blocks in Python).
* Text content of nodes and attributes should be wrapped with single or double quotes.
* Attribute is a `@` sign, followed by attribute name, followed by space followed by attribute value in quotes. Another way to describe attribute is an unrollable CSS selector (see below).
* CDATA sections should be wrapped with triple quotes.
* Namespace declaration is a `:` sign, followed by space, followed by namespace prefix, followed by space followed by namespace URL.
* Processing instruction is a `?` sign, followed by space, followed by processing instruction content.
* Doctype is a `!` sign, followed by space, followed by content. *Doctypes with complex content and custom entities are under consideration*.
* Empty lines are ignored.
* Everything that doesn't start with `:` followed by space, `@`, `?` or `!` is interpreted as an unrollable CSS selector and means node.
* There are single line comments (`// Here is the comment`) and multiline comments (`/* This thing could be multiline */`).
* You want to name your nodes in lower case with minus sign as separator: `some-node`, but *not `SomeNode`*. More on that is in *special namespace* section.


Unrollable CSS selector
-----------------------

Unrollable CSS selector is a CSS selector that unambiguously describes node name and attributes. It should start with node name. Node name could start with `:` prefollowed by namespace prefix.

Examples:

Unrollable CSS selector

    node#i.some[attr=value][another="another value"].other

Unrolls to

    <node id="i" class="some other" attr="value" another="another value">

And this one

    prefix:node[aaa=bbb]

Unrolls to

    <prefix:node aaa="bbb">


Examples
--------

This code:

    world[beautiful="indeed"] // One way to set attributes.
        hello
            @greeting "yes" // Another way to set attributes.
            nice
                "to"
            meet
                "you!"
        hi[again="true"]
            "!!!"

Goes to:

    <world beautiful="indeed">
        <hello greeting="yes">
            <nice>to</nice>
            <meet>you!</meet>
        </hello>
        <hi again="true">!!!</hi>
    </world>


This code:

    ? xml encoding="utf-8"
    root
        : ns1 "http://localhost/namespace1
        : ns2 "http://localhost/namespace2

        ns1:node1#id1
            ns2:node2.class1
                "text1"
            ns2:node3.class2
                "text2"

        ns2:node4
            node5#id2
                """ text3 """

Goes to:

    <?xml encoding="utf-8"?>
    <root
        xmlns:ns1="http://localhost/namespace1"
        xmlns:ns2="http://localhost/namespace2">

        <ns1:node1 id="id1">
            <ns2:node2 class="class1">text1</ns2:node2>
            <ns2:node3 class="class2">text2</ns2:node3>
        </ns1:node1>
        <ns2:node4>
            <node5 id="id2"><![CDATA[ text3 ]]></node5>
        </ns2:node4>
    </root>


Special namespace
-----------------

It sometimes happens that you have some special namespace in one hand and all the rest namespaces in the other. Let's consider XSLT templates as an example, you have a namespace for XSLT instructions and everything else is going to result document untouched.

Special namespace is declared with `:` sign, followed by space, followed by namespace URL (**no namespace prefix needed**).

Special namespace's node names should start with upper case letter (it will be lower cased in the result).

Here is how translation works (say, `sns` is a prefix for special namespace and `other` is a prefix for just some other namespace):

| IndentXML node name | XML node name | Comment |
|----------------|---------------|---------|
| `NODE` | `<sns:node>` | Node from special namespace |
| `Node` | `<sns:nODE>` | Only first upper case letter matters in special namespace detection, other letters case is inverted |
| `node` | `<node>` | Just unnamespaced node |
| `nODe` | `<nODe>` | Another unnamespaced node (first letter is in lower case) |
| `other:node` | `<other:node>` | Some node with explicitly defined namespace |
| `other:NoDe` | `<other:NoDe>` | It doesn't matter if first letter is in upper case, when node's namespace is defined explicitly |
| `:NODE` | `<NODE>` | If you still need unnamespaced nodes starting from upper case letter, here is the workaround (empty namespace prefix) |




This code:

    STYLESHEET[version="1.0"]
        : http://www.w3.org/1999/XSL/Transform

        TEMPLATE[match="/"]
            html
                head
                    title
                        VALUE-OF[select="'Hello'"]
                body
                    APPLY-TEMPLATES[select="node()"]
                    footer
                        "World"

Goes to:

    <xsl:stylesheet
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
        version="1.0">

        <xsl:template match="/">
            <html>
                <head>
                    <title>
                        <xsl:value-of select="'Hello'" />
                    </title>
                </head>
                <body>
                    <xsl:apply-templates select="node()" />
                    <footer>World</footer>
                </body>
            </html>
        </xsl:template>

    </xsl:stylesheet>


More
----

C code to serialize and deserialize Libxml2 trees is in progress. Here will be the link.
