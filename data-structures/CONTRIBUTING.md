# Contributing to DSA Training Ground

Thank you for your interest in contributing! This repository aims to be the most comprehensive DSA learning resource available. We welcome contributions from developers of all skill levels.

## 📋 Table of Contents

- [How to Contribute](#how-to-contribute)
- [Types of Contributions](#types-of-contributions)
- [Contribution Guidelines](#contribution-guidelines)
- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)

---

## 🤝 How to Contribute

### 1. Fork the Repository

Click the "Fork" button at the top right of this repository.

### 2. Clone Your Fork

```bash
git clone https://github.com/YOUR_USERNAME/DSA.git
cd DSA
```

### 3. Create a Branch

```bash
git checkout -b feature/your-feature-name
```

### 4. Make Your Changes

Follow the guidelines below for different types of contributions.

### 5. Commit Your Changes

```bash
git add .
git commit -m "Add: Brief description of your changes"
```

**Commit Message Format:**
- `Add:` for new content
- `Fix:` for corrections
- `Update:` for improvements to existing content
- `Docs:` for documentation changes

### 6. Push to Your Fork

```bash
git push origin feature/your-feature-name
```

### 7. Create a Pull Request

Go to your fork on GitHub and click "New Pull Request". Provide a clear description of your changes.

---

## 📝 Types of Contributions

### 1. Adding New Problems

**What to Include:**
- Clear problem statement
- Example test cases with expected outputs
- Constraints
- 3-5 progressive hints (not full solutions)
- Link to practice platform (LeetCode, HackerRank, etc.)

**Format:**
```markdown
#### Problem X: Problem Title
**Difficulty:** [Beginner/Easy/Medium/Hard/Expert/Advanced/Master]

**Problem Statement:**
[Clear description of the problem]

**Example:**
```
Input: [example input]
Output: [expected output]
Explanation: [brief explanation]
```

**Constraints:**
- [Constraint 1]
- [Constraint 2]

**Hints:**
1. [First hint - general approach]
2. [Second hint - more specific]
3. [Third hint - key insight]

**Test Cases:**
```
Test 1: [input] → Expected: [output]
Test 2: [input] → Expected: [output]
```

**Practice Platform:** [Platform Name] #[Problem Number]
```

### 2. Improving Explanations

- Clarify confusing concepts
- Add visual representations (ASCII art)
- Include more examples
- Fix typos and grammatical errors

### 3. Adding Implementations

- Provide language-agnostic pseudocode
- Keep it clear and well-commented
- Follow consistent naming conventions

### 4. Adding New Topics

If adding a completely new DSA topic:
- Follow existing README structure
- Include theory, implementation, problems
- Cover all difficulty levels
- Add real-world applications

### 5. Translating Content

We welcome translations to other languages:
- Create a new directory: `translations/[language_code]/`
- Maintain same structure as main repository
- Add link to translation in main README

### 6. Fixing Bugs

- Report bugs via GitHub Issues
- Provide clear steps to reproduce
- Submit fix with test cases

---

## 📐 Contribution Guidelines

### Content Quality Standards

#### For Problem Statements:
- ✅ Clear and unambiguous
- ✅ Include multiple test cases
- ✅ Cover edge cases
- ✅ Provide hints, not solutions
- ✅ Specify time/space constraints
- ❌ Don't include full code solutions
- ❌ Don't copy directly from other platforms

#### For Explanations:
- ✅ Explain "why" not just "how"
- ✅ Use simple language
- ✅ Include visual representations
- ✅ Provide complexity analysis
- ✅ Mention trade-offs
- ❌ Don't assume advanced knowledge
- ❌ Don't skip important steps

#### For Code/Pseudocode:
- ✅ Use meaningful variable names
- ✅ Add comments for complex logic
- ✅ Follow language-agnostic style
- ✅ Include base cases and edge case handling
- ❌ Don't use language-specific features heavily
- ❌ Don't write production code (keep it educational)

### Formatting Standards

#### Markdown:
- Use proper headings hierarchy (H1, H2, H3...)
- Include table of contents for long documents
- Use code blocks with syntax highlighting
- Use tables for comparisons
- Add blank lines for readability

#### Code Blocks:
```markdown
\```language
// Your code here
\```
```

#### Visual Representations:
```markdown
\```
ASCII art or diagrams
\```
```

### File Organization

```
DSA/
├── TopicName/
│   ├── README.md           # Main content
│   ├── implementations/    # (Optional) Example implementations
│   └── problems/          # (Optional) Additional problem files
```

### Naming Conventions

- **Directories:** PascalCase (e.g., `DynamicProgramming/`)
- **Files:** lowercase with hyphens (e.g., `problem-name.md`)
- **README.md:** Always uppercase

---

## ✅ Pull Request Checklist

Before submitting your PR, ensure:

- [ ] Content is original or properly attributed
- [ ] Follows repository structure and formatting
- [ ] No spelling or grammatical errors
- [ ] Problem statements include all required sections
- [ ] Code examples are clear and well-commented
- [ ] Related files are updated (if applicable)
- [ ] No copyright violations
- [ ] Commit messages are clear and descriptive

---

## 🚫 What Not to Contribute

- ❌ Full code solutions (only hints and pseudocode)
- ❌ Copyrighted content without permission
- ❌ Low-quality or duplicate content
- ❌ Promotional content or spam
- ❌ Off-topic material

---

## 🐛 Reporting Issues

Found a bug or error? Please report it!

### How to Report:
1. Go to [Issues](https://github.com/fmfalgun/DSA/issues)
2. Click "New Issue"
3. Choose appropriate template
4. Provide detailed description

### Include:
- **Type:** Bug/Error/Improvement/Question
- **Location:** File path and line number (if applicable)
- **Description:** Clear description of the issue
- **Expected vs Actual:** What you expected vs what you found
- **Suggestions:** (Optional) How to fix it

---

## 💬 Discussion and Questions

Have questions or ideas?
- Open a [Discussion](https://github.com/fmfalgun/DSA/discussions)
- Start a conversation about new features
- Ask for clarification on topics

---

## 🎯 Code of Conduct

### Our Standards

✅ **DO:**
- Be respectful and inclusive
- Provide constructive feedback
- Help others learn
- Give credit where due
- Assume good intentions

❌ **DON'T:**
- Use offensive language
- Make personal attacks
- Spam or promote unrelated content
- Share solutions to interview problems
- Plagiarize content

### Enforcement

Violations will result in:
1. **First offense:** Warning
2. **Second offense:** Temporary ban
3. **Third offense:** Permanent ban

---

## 🏆 Recognition

Contributors will be recognized in:
- Repository README
- Contributors page
- Release notes (for significant contributions)

---

## 📚 Resources for Contributors

### Learning Resources:
- [Markdown Guide](https://www.markdownguide.org/)
- [Git Basics](https://git-scm.com/book/en/v2/Getting-Started-Git-Basics)
- [Writing Good Commit Messages](https://chris.beams.io/posts/git-commit/)

### Inspiration:
- [How to Write Great Problem Statements](https://leetcode.com/discuss/general-discussion/)
- [Technical Writing Best Practices](https://google.github.io/styleguide/docguide/)

---

## ❓ FAQ

### Q: Can I add solutions in multiple programming languages?
**A:** We prefer language-agnostic pseudocode. If adding language-specific code, ensure it's educational and well-commented.

### Q: Can I add links to external resources?
**A:** Yes, but only if they're high-quality, free, and relevant. No affiliate links.

### Q: How long does review take?
**A:** Usually 2-7 days depending on the size of contribution.

### Q: Can I claim problems I've added?
**A:** All contributions are open-source under the repository license.

### Q: Can I add interview questions from specific companies?
**A:** Only add publicly available problems. Never share confidential interview questions.

---

## 📞 Contact

- **Issues:** [GitHub Issues](https://github.com/fmfalgun/DSA/issues)
- **Discussions:** [GitHub Discussions](https://github.com/fmfalgun/DSA/discussions)

---

## 📄 License

By contributing, you agree that your contributions will be licensed under the same license as this repository.

---

**Thank you for helping make this the best DSA learning resource! 🎓**

Every contribution, no matter how small, helps learners worldwide. Happy contributing!
