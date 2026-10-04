<sub>_[(How version numbering works in all my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/version-numbering.md)_</sub> | 
<sub>_[(My policy on A.I. in my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/ai-use-policy.txt)_</sub>

Creates a `.byfc` (Banyan Flowchart) file.

# Building

`BanyanChart.cbp` is a [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) solution file, so you will need that software to open the project. Converting to another solution format might work, as long as you have wxWidgets installed, (though [wxSmith](#Uses) will only work with Code::Blocks).

### Ubuntu

This project requires installation of `libwxgtk3.2-dev` if you run Ubuntu. It is available with this command: 

```
sudo apt update && sudo apt install -y libwxgtk3.2-dev libwxgtk-media3.2-dev libwxgtk-webview3.2-dev
```

# License

You may view the BSD 3-Clause Clear License [here](https://github.com/lunanerdderg/BanyanChart/blob/main/LICENSE), but the TL;DR is that you can use this project for whatever you like (except for patents), as long as:

* You retain the license, (and if distributing in binary format, include it in documentation and other materials)
* You do not use my name to endorse or promote anything without my permission

_(This is a simplified summary of the license and should not be taken as legal advice. Please consult a lawyer before taking any action.)_

### Utilizes:
* [wxWidgets (3.2.0)](https://github.com/wxWidgets/wxWidgets/tree/v3.2.0) uses a [modified GNU Library General Public License](https://github.com/wxWidgets/wxWidgets/blob/v3.2.0/docs/licence.txt)
* [wxSmith](https://wxsmithaddons.sourceforge.net/) is under the [GNU General Public License](http://www.gnu.org/licenses/gpl.html)
