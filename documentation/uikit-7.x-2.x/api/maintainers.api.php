<?php

/**
 * @defgroup maintainers Project Maintainers
 * @{
 * @lead maintaining Maintaining the UIkit project using git and drupal.org.
 * If you are a maintainer of the UIkit project, this topic goes over common
 * tasks to help automate the process of comitting your changes back to the
 * repository and creating release branches/tags. These topics are not helpful
 * unless you are a maintainer, but feel free to continue reading to learn how
 * the UIkit team has lessened the burden of extensive Drupal theme development.
 *
 * @subtitle Jump to a section
 * - @ref introduction
 * - @ref getting_started
 * - @ref git_maintainers
 * - @ref project_maintainers
 * - @ref issue_queue_maintainers
 * - @ref release_maintainers
 *
 * @divider
 *
 * @section introduction Introduction
 * Drupal 7 theme development is rewarding work that may seem overly repetitive
 * at times. The goal of these topics is to make common tasks far more
 * automated for you. Development tasks will be continuously improved over time,
 * so your feedback is greatly appreciated.
 *
 * If you have any questions or suggestions, feel free to create an issue in the
 * @link https://www.drupal.org/project/issues/uikit UIkit issue queue @endlink.
 *
 * @divider
 *
 * @section getting_started Getting Started
 * The level of access you have to the UIkit project as a co-maintainer depends
 * on the role assigned to you by the UIkit project lead.
 *
 * Once you request a co-maintainer role through the UIkit issue queue, one or
 * more of the following roles will be assigned to you:
 * - Git maintainer: Allows a user to commit or push to the repository
 *   associated with this project.
 * - Project co-maintainer: Allows a user to edit the drupal.org project page
 *   and modify its settings, as well as co-maintain the documentation site at
 *   uikit-drupal.org.
 * - Issue queue maintainer: Allows a user to assign issues to other issue
 *   maintainers for this project.
 * - Release maintainer: Allows a user to create and update releases, and to
 *   control which branches are recommended or supported.
 *
 * Another role (Administer maintainers) does exist, but will not be assigned to
 * anyone other than the project lead.
 *
 * Your initial roles will be assigned based on your level of expertise in one
 * or more of the above roles. Additional roles can be assigned as your
 * involvement in the project progresses.
 *
 * @alert uk-alert
 * Strict adherence to the
 * @link https://www.drupal.org/dcoc Drupal Code of Conduct @endlink is to be
 * expected, with those not in compliance being stripped of their project
 * role(s) at the sole discretion of the project lead.
 * @endalert
 *
 * @divider
 *
 * @section git_maintainers Git Maintainers
 * Git maintainers will be given access to commit and push changes to the git
 * repository for UIkit. Knowledge of basic git commands and development
 * workflow is a requirement to be a git maintainer, but you do not have to be
 * an expert. You will learn more complex git and workflow concepts as you
 * progress through maintaining the git respoitory, so we are here to assist
 * you if needed.
 *
 * Here are some topics to help Git maintainers:
 * - @link version_control Git Version Control @endlink
 * - @link project_release Creating a Project Release @endlink
 *
 * @divider
 *
 * @section project_maintainers Project Co-maintainers
 * Project co-maintainers will be given access to make changes to the project
 * page, which is the first place most members of the community will come across
 * when first introduced to the UIkit project.
 *
 * Here are some topics to help Project Co-maintainers:
 * - @link maintain_project Maintaining the UIkit Project @endlink
 *
 * @divider
 *
 * @section issue_queue_maintainers Issue Queue Maintainers
 * Issue queue maintainers will be given access to assign issues to other
 * co-maintainers involved in the UIkit project. This allows us to be sure
 * the issue will be handled by the co-maintainer with the best knowledge the
 * issue addresses.
 *
 * Here are some topics to help Issue Queue Maintainers:
 * - @link maintain_issue_queue Maintaining the Issue Queue @endlink
 *
 * @divider
 *
 * @section release_maintainers Release Maintainers
 * Release maintainers will be given access to create, edit and publish releases
 * for the UIkit project. They will also be able to assign recommended and
 * supported releases available on the project page.
 *
 * Here are some topics to help Release maintainers:
 * - @link publish_release Publishing a Project Release @endlink
 * @}
 */

/**
 * @defgroup version_control Version Control
 * @{
 * @lead git_commands Git version control for git maintainers.
 * Git maintainers may clone and push their changes back to the git repository.
 * The following contains the git commands to work on development of the UIkit
 * project.
 *
 * @divider
 *
 * @section cloning_project Cloning project (one time only)
 * Setting up this repository in your local environment for the first time is
 * easy. If you already have a local repository, skip this step. Replace
 * {username} with your Drupal.org Git username:
 *
 * @code
 * git clone --branch 7.x-2.x {username}@git.drupal.org:project/uikit.git
 * cd uikit
 * @endcode
 *
 * @divider
 *
 * @section routinely Routinely
 * The headings below are not sequential. What you choose to do depends on where
 * you are in your process.
 *
 * @heading h4 Checking your repository status @endheading
 * To see what you will commit by running git commit and what you could commit
 * by running git add before running git commit:
 *
 * @code
 * git status
 * @endcode
 *
 * @heading h4 Switching to a different branch @endheading
 * When you clone the repository you have access to all the branches and tags.
 * The first command shows your choices. The second command makes the switch:
 *
 * @code
 * git branch -a
 * git checkout [branchname]
 * @endcode
 *
 * @heading h4 Committing all changes locally @endheading
 * After making changes, add and commit them. Do not begin commit messages with
 * the # symbol:
 *
 * @code
 * git add -A
 * git commit -m "Issue #[issue number] by [usernames]: [Short summary]."
 * @endcode
 *
 * @heading h4 Pushing your code back to the repository on Drupal.org @endheading
 * @code
 * git push -u origin 7.x-2.x
 * @endcode
 *
 * @divider
 *
 * @section patching Patching
 * If you have not already cloned the repository, follow the directions above
 * for setting up this repository in your local environment. Be sure you are on
 * the branch you wish to patch, then ensure it is up-to-date with the following
 * command:
 *
 * @code
 * git pull origin 7.x-2.x
 * @endcode
 *
 * @heading h4 Creating a patch @endheading
 * For most improvements, use the following command after making your changes:
 *
 * @code
 * git diff >  [description]-[issue-number]-[comment-number].patch
 * @endcode
 *
 * For more complex improvements that require adding/removing files, work over
 * the course of multiple days including git commits, or collaboration with
 * others, see the
 * @link https://www.drupal.org/node/1054616 Advanced patch workflow @endlink.
 *
 * @heading h4 Applying a patch @endheading
 * Download the patch to your working directory. Apply the patch with the
 * following command:
 *
 * @code
 * git apply -v [patchname.patch]
 * @endcode
 *
 * To avoid accidentally including the patch file in future commits, remove it:
 *
 * @code
 * rm [patchname.patch]
 * @endcode
 *
 * @heading h4 When you're done: Reverting uncommited changes @endheading
 * Revert changes to a specific file:
 * @code
 * git checkout [filename]
 * @endcode
 *
 * Revert changes to the whole working tree:
 * @code
 * git reset --hard
 * @endcode
 *
 * @divider
 *
 * When you are ready to create and publish a new project release, see
 * @link project_release Creating a Project Release @endlink
 * @}
 */

/**
 * @defgroup project_release Creating a Project Release
 * @{
 * @lead project_releases Creating new project releases for the git repository.
 * Git maintainers may create new release branches and tags for the git
 * repository. The following contains the git commands to create releases.
 *
 * @divider
 *
 * @section creating_releases Creating Releases
 * See the
 * @link https://www.drupal.org/node/1015226 naming conventions @endlink
 * for a complete description of how to name branches and tags so you can create
 * releases.
 *
 * @heading h4 Branch for a dev release @endheading
 * This creates and checks out a new branch in one command, then pushes it to
 * Drupal.org:
 *
 * @code
 * git checkout -b 7.x-2.x
 * git push -u origin 7.x-2.x
 * @endcode
 *
 * @heading h4 Tag for an alpha/beta/rc testing release @endheading
 * This creates and checks out a new release tag, then pushes it to Drupal.org.
 * Replace 7.x-2.0-alpha1 with the correct tag naming conventions for the
 * release tag you are creating.
 *
 * @code
 * git checkout  7.x-2.x
 * git tag 7.x-2.0-alpha1
 * git push origin tag 7.x-2.0-alpha1
 * @endcode
 *
 * @heading h4 Tag for a stable release @endheading
 * This does the same, except for a stable release.
 *
 * @code
 * git checkout  7.x-2.x
 * git tag 7.x-2.0
 * git push origin tag 7.x-2.0
 * @endcode
 *
 * @divider
 *
 * Once you've pushed the properly formed tag or branch, see
 * @link publish_release Publishing a Project Release @endlink
 * for directions to actually create the release node on drupal.org (if you have
 * the Release maintainer role).
 * @}
 */

/**
 * @defgroup publish_release Publishing a Project Release
 * @{
 * @lead publish_releases Creating and publishing new project releases on drupal.org.
 * Release maintainers may create new release nodes on drupal.org. Release nodes
 * are used to provide the community with a downloadable package of the UIkit
 * project to use on their Drupal sites. Follow these instructions to create
 * and publish new release nodes.
 *
 * @subtitle Jump to a section
 * - @ref authoring_release_notes
 * - @ref release_notes_template
 * - @ref creating_release
 * - @ref publishing_release
 *
 * @divider
 *
 * @section authoring_release_notes Authoring Release Notes
 * Release notes provide information to the community about the release you are
 * going to create and publish below. To stay consistent we use a template so
 * each release can convey important information in an easy-to-read format.
 *
 * @alert uk-alert
 * If you do not have the Git maintainer role, please request the release notes
 * text to use in the template from a project maintainer with the Git maintainer
 * role. We have an automated task that can build the release notes for us that
 * requires Git access. Once you have the release notes continue to
 * @link http://uikit-drupal.com/api/uikit/documentation%21uikit-7.x-2.x%21api%21maintainers.api.php/group/publish_release/7.x-2.x#release_notes_template Release Notes Template @endlink.
 * @endalert
 *
 * For maintainers with the Git maintainer role, the following will
 * automatically build the release notes to use in the template.
 *
 * If not installed, run the following Drush command to download the
 * @link https://www.drupal.org/project/grn Git Release Notes for Drush @endlink
 * script. This script is a Drush command that generates release notes from
 * commits between two git reference objects.
 *
 * @codenophp drush dl grn @endcodenophp
 *
 * First change directories to the UIkit project's root directory in your
 * terminal. Then use one of the following commands to generate the release
 * notes.
 *
 * The @inlinecode <start> @endinlinecode and @inlinecode <end> @endinlinecode
 * arguments used in the examples below can be tag names or commit SHA1 hashes.
 * You can use a branch name for the @inlinecode <start> @endinlinecode argument
 * (for example, when you have not had a tag created yet). The
 * @inlinecode <end> @endinlinecode argument can also be a remote branch. The
 * @inlinecode --commit-count option @endinlinecode gives you the number of
 * commits between the
 * @inlinecode <start> @endinlinecode and @inlinecode <end> @endinlinecode
 * arguments.
 *
 * @codenophp drush rn <start> <end> --commit-count @endcodenophp
 *
 * For example when the branch is not checked out locally you may try something
 * like this:
 *
 * @codenophp drush rn 7.x-2.0-rc1 origin/7.x-2.x --commit-count @endcodenophp
 *
 * Or if both tags have already been pushed to the repository you may try
 * something like this:
 *
 * @codenophp drush rn 7.x-2.0-rc1 7.x-2.0-rc2 --commit-count @endcodenophp
 *
 * If you only provide the tag, the previous tag before that will be used as
 * the @inlinecode <end> @endinlinecode argument:
 *
 * @codenophp drush rn 7.x-2.0-rc2 @endcodenophp
 *
 * If both tags are ommitted, the latest tag will be used as the tag:
 *
 * @codenophp drush rn --commit-count @endcodenophp
 *
 * All four of the above examples will output the following to your terminal:
 *
 * @codehtml<p>Changes since 7.x-2.0-rc1 (3 commits):</p>
 * <ul>
 *   <li>Update package.json</li>
 *   <li>Status messages need top and bottom margin added</li>
 *   <li>Sidebar blocks need bottom margin added</li>
 * </ul>
 * @endcodehtml
 *
 * @divider
 *
 * @section release_notes_template Release Notes Template
 * Use the following template and instructions to create the release notes you
 * will use when creating the new release node on drupal.org.
 *
 * @codehtml<!-- (Optional) Insert important information here, if not conveyed in the
 * commit messages below. Keep this to one or two short, but descriptive,
 * sentences. Anything longer than that and we will create a change record. -->
 *
 * <p>Changes since <!-- git tag --> (<!-- # of commits --> commits):</p>
 *
 * <ul>
 * <li><!-- Issue/Commit message --></li>
 * </ul>
 * @endcodehtml
 *
 * Anything wrapped in @inlinecode <!-- @endinlinecode and
 * @inlinecode --> @endinlinecode will be replaced by the generated release
 * notes. The only difference is adding a short description before the generated
 * release notes.
 *
 * @divider
 *
 * @section creating_release Creating a New Release
 *
 * @divider
 *
 * @section publishing_release Publishing a New Release
 * @}
 */

/**
 * @defgroup maintain_project Maintaining the UIkit Project
 * @{
 * @lead maintaining_project Maintaining the UIkit project on drupal.org.
 * @}
 */

/**
 * @defgroup maintain_issue_queue Maintaining the Issue Queue
 * @{
 * @lead maintaining_issue_queue Maintaining the UIkit issue queue on drupal.org.
 * @}
 */
