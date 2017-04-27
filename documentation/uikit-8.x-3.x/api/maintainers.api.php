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
 * Drupal 8 theme development is rewarding work that may seem overly repetitive
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
 * git clone --branch 8.x-3.x {username}@git.drupal.org:project/uikit.git
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
 * git push -u origin 8.x-3.x
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
 * git pull origin 8.x-3.x
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
 * git checkout -b 8.x-3.x
 * git push -u origin 8.x-3.x
 * @endcode
 *
 * @heading h4 Tag for an alpha/beta/rc testing release @endheading
 * This creates and checks out a new release tag, then pushes it to Drupal.org.
 * Replace 8.x-2.0-alpha1 with the correct tag naming conventions for the
 * release tag you are creating.
 *
 * @code
 * git checkout  8.x-3.x
 * git tag 8.x-2.0-alpha1
 * git push origin tag 8.x-2.0-alpha1
 * @endcode
 *
 * @heading h4 Tag for a stable release @endheading
 * This does the same, except for a stable release.
 *
 * @code
 * git checkout  8.x-3.x
 * git tag 8.x-2.0
 * git push origin tag 8.x-2.0
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
 * - @ref release_stage_messages
 * - @ref release_notes_template
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
 * @link http://uikit-drupal.com/api/uikit/documentation%21uikit-8.x-3.x%21api%21maintainers.api.php/group/publish_release/8.x-3.x#release_notes_template Release Notes Template @endlink.
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
 * @selectcode drush dl grn @endselectcode
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
 * @inlinecode --commit-links option @endinlinecode gives you links to the
 * commits between the
 * @inlinecode <start> @endinlinecode and @inlinecode <end> @endinlinecode
 * arguments.
 *
 * @selectcode drush rn <start> <end> --commit-links @endselectcode
 *
 * For example when the branch is not checked out locally you may try something
 * like this:
 *
 * @selectcode drush rn 8.x-2.0-beta1 origin/8.x-3.x --commit-links @endselectcode
 *
 * Or if both tags have already been pushed to the repository you may try
 * something like this:
 *
 * @selectcode drush rn 8.x-2.0-beta1 8.x-2.0-beta2 --commit-links @endselectcode
 *
 * If you only provide the tag, the previous tag before that will be used as
 * the @inlinecode <end> @endinlinecode argument:
 *
 * @selectcode drush rn 8.x-2.0-beta2 --commit-links @endselectcode
 *
 * If both tags are omitted, the latest tag will be used as the tag:
 *
 * @selectcode drush rn --commit-links @endselectcode
 *
 * All four of the above examples will output the following to your terminal:
 *
 * @codehtml<p>Changes since 8.x-2.0-beta1:</p>
 * <ul>
 * <li>Remove get.inc (<a href="http://drupalcode.org/uikit.git/commit/2549f5e" title="View commit">#</a>)</li>
 * <li>Add navbar menu block template (<a href="http://drupalcode.org/uikit.git/commit/1855916" title="View commit">#</a>)</li>
 * <li>Add navbar header and divider support (<a href="http://drupalcode.org/uikit.git/commit/98b0c85" title="View commit">#</a>)</li>
 * <li>Update documentation and remove obsolete theme.inc (<a href="http://drupalcode.org/uikit.git/commit/8fed1aa" title="View commit">#</a>)</li>
 * </ul>
 * @endcodehtml
 *
 * @divider
 *
 * @section release_stage_messages Release Stage Messages
 * Each release stage has a different message to include in the release notes.
 * Use one of the following based on the release stage you are publishing in,
 * replacing @inlinecode <!-- UIkit 8.x-2.0 --> @endinlinecode with the correct
 * feature series the release is in.
 *
 * @subtitle Alpha Release (i.e. 8.x-2.0-alpha1, 8.x-2.0-alpha2, etc.)
 * @selectcode This is an <strong>alpha release for the next feature release of <!-- UIkit 8.x-2.0 --></strong>. Alphas are good testing targets for developers and site builders who are comfortable reporting (and where possible, fixing) their own bugs. Alpha releases are not recommended for non-technical users, nor for production websites. Thorough testing is still needed in case there are unknown bugs. @endselectcode
 *
 * @subtitle Beta Release (i.e. 8.x-2.0-beta1, 8.x-2.0-beta2, etc.)
 * @selectcode This is a <strong>beta release for the next feature release of <!-- UIkit 8.x-2.0 --></strong>. Betas are good testing targets for developers and site builders who are comfortable reporting (and where possible, fixing) their own bugs. Beta releases are not recommended for non-technical users, nor for production websites. @endselectcode
 *
 * @subtitle Release Candidate (i.e. 8.x-2.0-rc1, 8.x-2.0-rc2, etc.)
 * @selectcode This is a <strong>release candidate for the next feature release of <!-- UIkit 8.x-2.0 --></strong>. Release candidates are not supported for production sites, but they are intended for widespread testing in preparation for the upcoming stable release. @endselectcode
 *
 * @subtitle Feature Release (i.e. 8.x-2.0, 8.x-2.1, etc.)
 * @selectcode This is a <strong>feature release in the UIkit 8.x-3.x series</strong> and is ready for use on production sites. @endselectcode
 *
 * @divider
 *
 * @section release_notes_template Release Notes Template
 * Use the following template and instructions to create the release notes you
 * will use when creating the new release node on drupal.org.
 *
 * @bold Important @endbold: Do NOT include the generated release notes for new
 * feature releases (i.e. 8.x-2.0, 8.x-2.1, etc.). The alpha/beta/rc releases
 * will already have all changes documented in their releases.
 *
 * @codehtml<!-- See Release Stage Messages above for message to enter here. -->
 *
 * <h3>Changes since <!-- git tag -->:</h3>
 * <ul>
 * <li><!-- Issue/Commit message and link --></li>
 * </ul>
 * @endcodehtml
 *
 * Anything wrapped in @inlinecode <!-- @endinlinecode and
 * @inlinecode --> @endinlinecode will be replaced by the generated release
 * notes. The only difference is adding a short description before the generated
 * release notes and changing the <p></p> paragraph tags with <h3></h3> heading
 * tags.
 *
 * @divider
 *
 * @section publishing_release Publishing a New Release
 * Publishing a release will provide a new downloadable package on the
 * drupal.org project page for UIkit. Only two types of releases are able to be
 * published:
 * - Release branch (i.e. 8.x-3.x, 7.x-3.x, etc.)
 * - Release tag (i.e. 8.x-2.0-alpha1, 8.x-2.0-beta2, etc.)
 *
 * Once you have the release notes ready from the steps above, visit the
 * @link https://www.drupal.org/node/add/project-release/2605968 add new release @endlink
 * page for the UIkit project. If there are no valid branches or tags found in
 * the git repository, contact a project maintainer so a new branch/tag can be
 * created. Once drupal.org is able to verify a valid branch/tag, select the
 * branch/tag you are creating a release for.
 *
 * On the next page you will enter the release notes. Using the template above,
 * with necessary changes made, copy and paste the release notes into the text
 * area provided.
 *
 * Always use the preview button before saving the new release so you can verify
 * the release notes are formatted correctly. Make any further necessary changes
 * and save the new release. The new release will then be shown to you.
 *
 * It will take drupal.org a few minutes to build the downloadable packages and
 * publish the new release. This is automatic, so please be patient. Once
 * drupal.org has completed those steps, the new release will be listed under
 * the download section of the UIkit project page. If this is a new branch
 * release, a new row for that release will appear in the download table. If
 * this is a new tag release, it will replace the previous tag release in the
 * series.
 * @}
 */

/**
 * @defgroup maintain_project Maintaining the UIkit Project
 * @{
 * @lead maintaining_project Maintaining the UIkit project on drupal.org.
 * Project co-maintainers are given permissions to make changes to the
 * @link https://www.drupal.org/project/uikit UIkit project page @endlink.
 *
 * If you do not have a drupal.org account, please
 * @link https://register.drupal.org/user/register create a new account @endlink
 * first. Then contact a UIkit project maintainer so they can add the project
 * co-maintainer role to your account.
 *
 * Once you have a drupal.org user account and the co-maintainer role, you can
 * make changes to the UIkit project page using the
 * @link https://www.drupal.org/node/2605968/edit edit @endlink form. The edit
 * page contains three sections of the UIkit project you can make changes to.
 * Each section is detailed below:
 *
 * @subtitle Jump to a section
 * - @ref edit_project
 * - @ref edit_releases
 * - @ref edit_default_branch
 *
 * @section edit_project Edit Project
 * The following details the different sections of the project page to edit:
 * - Name: The name that will appear as the title of the project page. This
 *   should always be @inlinecode UIkit @endinlinecode.
 * - Short name: The namespace to use for drupal.org project. This cannot be
 *   changed and will always be @inlinecode uikit @endinlinecode.
 * - Images: These are displayed on the right-hand side of the project page,
 *   usually screenshots of the UIkit theme to give users an example of how the
 *   theme looks on a normal Drupal site. The @inlinecode alt @endinlinecode for
 *   each image will display as text in-place of the image if there is an issue
 *   displaying the image on the project page. Multiple images can be displayed
 *   and will be shown on the project page in the order they appear on the edit
 *   form. Use the drag-and-drop feature to reorder the images.
 * - Project classification: Contains useful information about the current
 *   status of the UIkit project. There are three fields available here:
 *   - Maintenance status: The current overall status of the project.
 *   - Development status: The level of development currently being performed.
 *   - Security advisory coverage: The current security advisory level of the
 *     project. This can only be changed by the
 *     @link https://www.drupal.org/drupal-security-team/general-information Drupal Security Team @endlink.
 * - Description: The text that is shown to users visiting the UIkit project
 *   page. You can provide a brief summary to be used on certain drupal.org
 *   pages by selecting @inlinecode Edit summary @endinlinecode and entering
 *   a short, descriptive summary of the project. Limit this to two or three
 *   sentences.
 * - File attachments: We currently do not allow adding any file attachments to
 *   the project page, so please leave this field as-is.
 * - Supporting organizations: The organizations who help contribute to the
 *   UIkit project. Multiple organizations can be added by selecting
 *   @inlinecode Add another item @endinlinecode.
 * - Revision information: A short explanation as to why you made changes to the
 *   project page.
 * - Issues: Configures the issue queue settings for the UIkit project. This
 *   should not need any changes, so please keep the settings as-is.
 * - Resources: Basic information about the UIkit project to be listed on the
 *   sidebar of the UIkit project page. These will be listed as links, so enter
 *   a valid URL visitors can visit. The following options are:
 *   - Screenshots: Links to a page that provides screenshots of the UIkit
 *     theme being used on a Drupal site.
 *   - Documentation: Links to a project documentation page, such as this site.
 *   - Demo: Links to a page where the user can try out a demo of the UIkit
 *     project.
 *   - Changelog: Links to a page where the user can view changelog records of
 *     the UIkit project.
 *   - Homepage: Links to the homepage of the UIkit project, such as this site.
 * - Project documentation: Drupal allows project maintainers to create
 *   documentation on drupal.org for contributed projects. This is an
 *   autocomplete form, so only valid documentation guides are allowed.
 *
 * @divider
 *
 * @section edit_releases Edit Releases
 * When editing releases you are configuring which major versions of the UIkit
 * project are supported and recommended for download. There are two sections:
 * - 8.x: Releases of UIkit for Drupal 8.
 * - 7.x: Releases of UIkit for Drupal 7.
 *
 * Each major version for each Drupal version will be listed with the most
 * current release for each major version. Only one major version is unsupported
 * at this time: 7.x-1.x-dev.
 *
 * The recommended major version for each Drupal version will tell drupal.org
 * which major version should be selected by default for various tasks, such as
 * downloading the UIkit project using
 * @link http://www.drush.org Drush @endlink or when checking the update status
 * on a Drupal site using the UIkit project.
 *
 * This should always be the major version of the UIkit project that supports
 * the latest stable release of the UIkit framework (currently 8.x-3.x and
 * 8.x-3.x).
 *
 * @divider
 *
 * @section edit_default_branch Edit Default Branch
 * The default branch tells drupal.org which branch should be downloaded when a
 * user clones the UIkit project using Git and which branch to show by default
 * in the @link http://drupalcode.org/uikit UIkit repository @endlink.
 *
 * This should always be the most recent stable major version of the UIkit
 * project that supports the latest stable release of the UIkit framework
 * (currently 8.x-3.x since 8.x-3.x is still under development).
 * @}
 */

/**
 * @defgroup maintain_issue_queue Maintaining the Issue Queue
 * @{
 * @lead maintaining_issue_queue Maintaining the UIkit issue queue on drupal.org.
 * Issue maintainers are given access to assign project issues to other
 * co-maintainers of the UIkit project. This ensures an issue is handled by the
 * appropriate project maintainer.
 *
 * The @link https://www.drupal.org/project/issues/uikit issue queue @endlink
 * for the UIkit project contains issues filed by drupal.org users. This is not
 * limited to co-maintainers of the UIkit project, but can be anyone with a
 * drupal.org user account.
 *
 * Some issues will be more targeted towards a co-maintainer with the skillset
 * to handle that issue, such as a designer or developer. If you are unsure if
 * the issue should be assigned or not, contact a project co-maintainer. They
 * can help you decide if the issue should be assigned and to whom.
 *
 * To assign an issue to a co-maintainer, go to the issue by selecting the link
 * for the issue under the @inlinecode Summary @endinlinecode in the
 * @link https://www.drupal.org/project/issues/uikit issue queue @endlink table.
 * Under the issue description is the @inlinecode Issue metadata @endinlinecode,
 * which configures the issue so drupal.org can organize it throughout the site.
 *
 * Select the @inlinecode Assign @endinlinecode box and choose which
 * co-maintainer the issue should be assigned to. Write a short message in the
 * @inlinecode Comment @endinlinecode field to let others know you have assigned
 * the issue to someone, then select @inlinecode Save @endinlinecode at the
 * bottom of the page. The co-maintainer you selected will then be notified of
 * the change.
 * @}
 */
