# IndentedXML

**IndentedXML** doesn't describe some new markup language. This format is just
another (more simple in some sense) way to represent **XML documents**.


## Basic principles

### Nodes

Parent-child relation is done with indentation (like code blocks in Python),
no closing tag is needed, no angle brackets are needed.

    root
        child
            subchild

instead of

    <root>
        <child>
            <subchild/>
        </child>
    </root>


### Attributes

Two ways to declare attributes.

    root attr1="hello" attr2="world"

or

    root
        @attr1 "hello"
        @attr2 "world"

instead of

    <root attr1="hello" attr2="world"/>


### Text nodes

JavaScript-like strings (in single or double quotes).

    root
        "hello\nworld"
        'HELLO\nWORLD'

instead of

    <root>hello
    worldHELLO
    WORLD</root>


### CDATA sections

Like text nodes but in triple quotes

    root
        """<hello>\"<world>"""

instead of

    <root><![CDATA[<hello>"<world>]]></root>


### Namespace declaration and namespaced nodes

    root
        : https://namespce.url
        : ns1 https://another.url
        ns1:child
            : ns2 https://more.url
            ns2:subchild

instead of

    <root xmlns="https://namespce.url" xmlns:ns1="https://another.url">
        <ns1:child xmlns:ns2="https://more.url">
            <ns2:subchild/>
        </ns1:child>
    </root>


### Processing instructions

    ? xml encoding="utf-8"
    root

instead of

    <?xml encoding="utf-8"?>
    <root/>


### Doctypes

    ! html

instead of

    <!DOCTYPE html>

and (for multiline doctypes)

    !
        html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"

instead of

    <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
     "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">


### Comments

Single line comments and multiline comments.

    // Hello
    root
        /*
            world
        */
        child

instead of

    <!-- Hello -->
    <root>
        <!--
            world
        -->
        <child/>
    </root>


### Empty lines

Empty lines are ignored.


### Entities

Entities are nearly the same.

    root
        "Hello "
        &amp
        " world"

instead of

    <root>Hello &amp; world</root>

### Special namespace

Sometimes you have some special namespace in one hand and all the rest
namespaces in the other. Let's consider XSLT templates as an example, you have
namespace for XSLT instructions and everything else is going to result document
untouched.

Special namespace's node names should start with upper case letter (it will be
lower cased in the result).

Special namespace is declared with `::` (only one special namespace per
document is allowed).

    STYLESHEET version="1.0"
        :: xsl http://www.w3.org/1999/XSL/Transform

        TEMPLATE match="/"
            html
                head
                    title
                        VALUE-OF select="'Hello'"
                body
                    APPLY-TEMPLATES select="node()"
                    footer
                        "World"

instead of

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


Here is how translation works (say, `sns` is a prefix for special namespace and
`other` is a prefix for just some other namespace):

| IndentedXML node name | XML node name | Comment |
|----------------|---------------|---------|
| `NODE` | `<sns:node>` | Node from special namespace |
| `Node` | `<sns:nODE>` | Only first upper case letter matters in special namespace detection, other letters case is inverted |
| `node` | `<node>` | Just unnamespaced node |
| `nODe` | `<nODe>` | Another unnamespaced node (first letter is in lower case) |
| `other:node` | `<other:node>` | Some node with explicitly defined namespace |
| `other:NoDe` | `<other:NoDe>` | It doesn't matter if first letter is in upper case, when node's namespace is defined explicitly |
| `:NODE` | `<NODE>` | If you need unnamespaced nodes starting from upper case letter, here is the workaround (empty namespace prefix) |


### Examples

Code

    world beautiful="indeed" // One way to set attributes.
        hello
            @greeting "yes" // Another way to set attributes.
            nice
                "to"
            meet
                "you!"
        hi again="true"
            "!!!"

goes to

    <world beautiful="indeed">
        <hello greeting="yes">
            <nice>to</nice>
            <meet>you!</meet>
        </hello>
        <hi again="true">!!!</hi>
    </world>


Code

    ? xml encoding="utf-8"
    root
        : ns1 http://localhost/namespace1
        : ns2 http://localhost/namespace2

        ns1:node1 id="id1"
            ns2:node2 class="class1"
                "text1"
            ns2:node3 class="class2"
                "text2"

        ns2:node4
            node5 id="id2"
                """ text3 """

goes to

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


### Some edge cases

#### Attribute values with entities

Code

    root attr1="value & value"
        @attr2
            "hello "
            &amp
            " world"

goes to

    <root attr1="value &amp; value"
          attr2="hello &amp; world"/>


#### Automatic string escaping

Code

    root attr1='This is "some" <value>'
        'And "some" <text>'

goes to

    <root attr1="This is &quot;some&quot; &lt;value&gt;">And "some" &lt;text&gt;</root>
