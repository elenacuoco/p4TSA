# Contributing to p4TSA

Changes reach `master` through pull requests only, and a pull request merges
only once CI is green. Nobody pushes to `master` directly, including the
maintainer.

## Making a change

```bash
git checkout -b short-description-of-the-change
# work, commit
git push -u origin short-description-of-the-change
gh pr create --fill        # or open the PR from the GitHub web interface
```

Build and test locally before you push. The native dependencies come from
conda-forge:

```bash
conda install -c conda-forge cxx-compiler cmake make scikit-build-core \
  pybind11 numpy scipy gsl fftw framel libboost-headers cereal pytest
pip install -e . --no-build-isolation
pytest python-wrapper/tests/ -v
```

## What CI checks

Every pull request runs, and all of it must pass:

| Job | What it does |
|-----|--------------|
| `Build + test (Python 3.10 / 3.11 / 3.12)` | Builds the C++ core and the `pytsa` binding on each supported Python, imports it, and runs the test suite. |
| `Docs build check` | Runs Doxygen and builds the Sphinx documentation, so a broken directive or a missing symbol page fails. |

## What to keep in mind

- **The candidate wavelet bases must stay orthonormal.** The detection
  statistic is the coefficient norm on the noise scale, and it is only the
  matched-filter signal-to-noise ratio of the reconstruction because Parseval
  holds. A biorthogonal basis silently breaks that identity, which is why the
  B-spline family is excluded — see `WDF2Classify.cpp`.
- **Thresholding is hard, not soft.** Soft thresholding shrinks every survivor
  by the threshold, biasing amplitudes low by an amount that grows with how
  many coefficients a signal is spread over. A denoised reconstruction wants
  that; a detection statistic and a parameter estimate do not.
- **Anything that changes trigger values needs a CHANGELOG entry** under
  *Notes for downstream users*, saying what moved and in which direction.
  `wdflow`'s golden-output test pins these numbers and will fail loudly.
- Follow the existing style of the C++ core and the pybind11 binding, and keep
  the Doxygen comments on anything public.

## For the maintainer: enforcing this

The rule above is a repository setting, not something in this file. Enable it
once, on GitHub, under *Settings → Branches → Add branch ruleset* for `master`:
require a pull request before merging, and require these status checks:

```
Build + test (Python 3.10)
Build + test (Python 3.11)
Build + test (Python 3.12)
Docs build check
```

Tick *Do not allow bypassing the above settings* so it applies to
administrators too — otherwise the maintainer keeps a direct-push path and the
rule is advisory.

The same thing from the command line:

```bash
gh api -X PUT repos/elenacuoco/p4TSA/branches/master/protection \
  -F required_pull_request_reviews[required_approving_review_count]=0 \
  -F required_status_checks[strict]=true \
  -F 'required_status_checks[contexts][]=Build + test (Python 3.10)' \
  -F 'required_status_checks[contexts][]=Build + test (Python 3.11)' \
  -F 'required_status_checks[contexts][]=Build + test (Python 3.12)' \
  -F 'required_status_checks[contexts][]=Docs build check' \
  -F enforce_admins=true \
  -F restrictions=
```

A status check can only be marked as required after it has reported once, so
push the workflow first and let it run one pull request before adding the rule.
