# Testing [anmonterio/bucklescript]()

```sh
letop-bs-example on  main [?] is 📦 v1.0.0 via ⬢ v14.15.4
 [I] ➜ node src/Basic.bs.js
Success

letop-bs-example on  main [?] is 📦 v1.0.0 via ⬢ v14.15.4
 [I] ➜ node src/App.bs.js
ok 13
ok2 13

letop-bs-example on  main [?] is 📦 v1.0.0 via ⬢ v14.15.4
 [I] ➜ node src/Day04.bs.js
internal/modules/cjs/loader.js:883
  throw err;
  ^

Error: Cannot find module 'bs-platform/lib/js/stdlib.js'
Require stack:
- /Volumes/SSD/Github/letop-bs-example/src/Day04.bs.js
    at Function.Module._resolveFilename (internal/modules/cjs/loader.js:880:15)
    at Function.Module._load (internal/modules/cjs/loader.js:725:27)
    at Module.require (internal/modules/cjs/loader.js:952:19)
    at require (internal/modules/cjs/helpers.js:88:18)
    at Object.<anonymous> (/Volumes/SSD/Github/letop-bs-example/src/Day04.bs.js:5:14)
    at Module._compile (internal/modules/cjs/loader.js:1063:30)
    at Object.Module._extensions..js (internal/modules/cjs/loader.js:1092:10)
    at Module.load (internal/modules/cjs/loader.js:928:32)
    at Function.Module._load (internal/modules/cjs/loader.js:769:14)
    at Function.executeUserEntryPoint [as runMain] (internal/modules/run_main.js:72:12) {
  code: 'MODULE_NOT_FOUND',
  requireStack: [ '/Volumes/SSD/Github/letop-bs-example/src/Day04.bs.js' ]
}
```
