<sub>_[(How version numbering works in all my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/version-numbering.md)_</sub> | 
<sub>_[(My policy on A.I. in my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/ai-use-policy.txt)_</sub>

# Building

`BanyanChart.cbp` is a [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) solution file, so you will need that software to open the project. Converting to another solution format probably won't work, since this project uses the Code::Blocks-exclusive plugin [wxSmith](#Uses).

## Ubuntu

This project requires installation of `libwxgtk3.2-dev` if you run Ubuntu. It is available with this command: 

```
sudo apt update && sudo apt install -y libwxgtk3.2-dev
```

# License

You may view the The Clear BSD License [here](https://github.com/lunanerdderg/Reefbackend/blob/main/LICENSE), but the TL;DR is that you can use this project for whatever you like except for patents, as long as:

* You retain the copyright notice and disclaimer

<sub>

<details>

  <summary>(Expand notice + Disclaimer)</summary>
  
```
BanyanChart Copyright (C) 2026 lunanerdderg

DISCLAIMER

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
```

</details>

</sub>

* You do not use my name to endorse or promote anything without my permission

_(This is a simplified summary of the license and should not be taken as legal advice. Please consult a lawyer before taking any action.)_

#### Uses:
* [wxWidgets (3.2.0)](https://github.com/wxWidgets/wxWidgets/tree/v3.2.0) uses a [modified GNU Library General Public License](https://github.com/wxWidgets/wxWidgets/blob/v3.2.0/docs/licence.txt)
* [wxSmith](https://wxsmithaddons.sourceforge.net/) is under the [GNU General Public License](http://www.gnu.org/licenses/gpl.html)
