# CRouter
C Router middleware for WSGI application frameworks.

WIP, please call back soon...

### Install
```bash
pip install crouter
```

### Examples

```python
from crouter import CRouter

class HomeHandler:

    def get(self, req, resp):
        return {}

routes = [
    ("/", HomeHandler),
]


if __name__ == "__main__":
    router = CRouter()
    router.parse(routes)
```

