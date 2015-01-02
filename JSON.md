# IndentedJSON

A way to represent JSON in an indented syntax.

```json
{
    "string": "Some string",
    "number": 123,
    "boolean": true,
    "null": null,
    "array": [
        "Some string",
        123,
        true,
        null,
        {"key": "value", "key2": 456}
        [234, 435]
    ],
    "object": {
        "key": "value",
        "key2": ["value2"],
        "key3": {"value": 3}
    }
}
```

Could be written like:

```json
{}
    string
        "Some string"
    number
        123
    boolean
        true
    null
        null
    array []
        "Some string"
        123
        true
        null
        {}
            key
                "value"
            key2
                456
        []
            234
            435
    object {}
        key
            "value"
        key2 []
            "value2"
        key3 {}
            value
                3
```

