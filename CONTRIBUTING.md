# CONTRIBUTING

This file describes the Git workflow you must follow for your submission.

---

## Getting started

> 🚨 **Use "Use this template" — do NOT Fork.**  
> If you Fork this repository your Pull Requests will target the template, not your own repo.  
> Click **"Use this template"** → "Create a new repository" to get your own independent copy.

---

## Branching workflow

### 1. Create a feature branch

Never work directly on `main`.

```bash
git checkout main
git pull origin main
git checkout -b your-feature-branch
```

Good branch name examples: `chess-engine`, `feature/piece-movement`, `exercise1`.

### 2. Develop and commit

Make your changes, then commit regularly with clear messages:

```bash
git add <files>
git commit -m "Add Rook move validation"
```

### 3. Push your branch

```bash
git push origin your-feature-branch
```

### 4. Open a Pull Request

On GitHub, open a Pull Request from `your-feature-branch` into `main` **of your own repository**.

> 🚨 Before opening the PR, verify that the **base repository** shown at the top of the PR form is **your own repository**, not the template. If it shows the template, close the PR and check that you used "Use this template" correctly.

### 5. Check CI and review

- Wait for all CI checks to pass (Build Linux, Build Windows, clang-tidy).
- Review your diff carefully in GitHub's diff viewer.
- If CI fails, fix the issue, push again, and wait for CI to re-run.

### 6. Merge and submit

- Merge the PR into `main`.
- Submit the repository link via Moodle.

---

## Conflict management

If your branch diverges from `main`, rebase before opening the PR:

```bash
git checkout your-feature-branch
git fetch origin
git rebase origin/main
```

Resolve any conflicts, then:

```bash
git add <resolved-files>
git rebase --continue
git push origin your-feature-branch --force
```

---

## Best practices

1. Keep commits focused — one logical change per commit.
2. Write commit messages in imperative form: `Add Bishop validation`, not `Added` or `Adding`.
3. Do not commit compiled binaries, `.o` files, or the `build/` directory.
4. Run `clang-format` on your code before committing.
